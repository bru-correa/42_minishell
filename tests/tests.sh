#!/bin/bash

# WARNING: USE THIS WITH "make test"!!!

# GLOBAL VARIABLES #
minishell="./minishell"
mini_prompt=$(echo -e "\nexit\n" | $minishell | head -n 1 | tr -d '\n')
valgrind_flags="valgrind --leak-check=full --show-leak-kinds=all --quiet"
valgrind_flags="$valgrind_flags --track-origins=yes"
valgrind_flags="$valgrind_flags --suppressions=readline.supp "
sh_outfile="./tests/sh_output.txt"
bash_outfile="./tests/bash_output.txt"

function display_banner() {
  echo -e "\033[0;31m"
  cat ./tests/banner.txt
  echo -e "                    Press ENTER to continue"
  echo -e "\033[0m"
  read END
  clear
}

function display_test_name() {
  echo -e "\033[0;35m"
  echo 🧪 "$1"
  echo "<--------------------------------------------------------------------->"
  echo -e "\033[0m"
} 

# TODO: Check exit signal
# Reset $sh_outfile and $bash_outfile every time
function run_test() {
  local test_name="$1"
  local cmd="$2"
  display_test_name "$test_name"
  local mini_output=$(echo -e "$cmd\nexit" | $minishell 2>/dev/null | grep -v "$mini_prompt")
  local bash_output=$(echo -e "$cmd" | bash 2> /dev/null)
  local leak=$(echo -e "$cmd\nexit" | $valgrind_flags $minishell 2>&1 1>/dev/null)
  if [[ -n "$leak"  && "${leak:0:2}" == "==" ]]; then
    echo "🟡 LEAKED"
    echo "$leak"
    exit 1
  elif [[ "$mini_output" == "$bash_output" ]]; then
    echo "🟢 PASSED"
  else
    diff <(echo "$mini_output") <(echo "$bash_output")
    echo "🔴 FAILED"
    exit 1
  fi
}

function display_section() {
  echo -e "\033[0;31m"
  echo "########## 😈 $1 😈 ##########"
  echo -e "\033[0m"
}

########### MAIN ###########

# display_banner

run_test "echo Hello World" "echo Hello World"
run_test "cat file" "cat ./minishell.c"
run_test "invalid cmd" "ekko hello world"
run_test "full path cat" "/bin/cat ./minishell.c"
run_test "empty line" ""
run_test "redirect output" "ls > file.txt"

# TODO: IDEAS:
# * Put all tests in a list, so you can target a test by passing it's index
# * 🟢 PASS, 🔴 FAILED, or 🟡 LEAK after the test (on the next line)
# * Print Received in RED with the output of minishell
# * Print Expected in GREEN with the output of bash
# * Save the bash outputs in a file
# * Test entire section at a time, and you can target sections too
# * Options inside the test script to load sections or specific tests
# * Doomslayer helmet in green at the end if pass on all tests (maybe sections too?)
# * Setup and create config file at the first time, prompting for minishell location
