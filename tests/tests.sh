#!/bin/bash

# WARNING: USE THIS WITH "make test"!!!

# GLOBAL VARIABLES #
minishell="./minishell"
mini_prompt=$(echo -e "\nexit\n" | $minishell | head -n 1 | tr -d '\n')
valgrind_flags="valgrind --leak-check=full --show-leak-kinds=all --quiet"
valgrind_flags="$valgrind_flags --track-origins=yes"
valgrind_flags="$valgrind_flags --suppressions=readline.supp "
outfile="./tests/outfile.txt"

function display_banner() {
  echo -en "\033[0;31m"
  cat ./tests/banner.txt
  echo "                    Press ENTER to continue"
  echo -en "\033[0m"
  read END
  clear
}

function display_diff_output() {
  local mini_ouput="$1"
  local expected="$2"
  local diff_output=$(diff <(echo "$1") <(echo "$2"))
  if [[ -n "$diff_output" ]]; then
    echo -en "\033[0;34m"
    echo "OUTPUT DIFF:"
    echo -en "\033[0;31m"
    echo "$diff_output"
    echo -en "\033[0m"
  fi
}

function display_diff_outfile() {
  local mini_ouput="$1"
  local expected="$2"
  local diff_output=$(diff <(echo "$1") <(echo "$2"))
  if [[ -n "$diff_output" ]]; then
    echo -en "\033[0;34m"
    echo "OUTFILE DIFF:"
    echo -en "\033[0;31m"
    echo "$diff_output"
    echo -en "\033[0m"
  fi
}

function display_passed() {
  echo -en "\033[0;32m"
  echo "🟢 PASSED"
  echo -en "\033[0m"
}

function display_leaked() {
  echo -en "\033[1;33m"
  echo "🟡 LEAKED"
  echo -en "\033[0m"
}

function display_failed() {
  echo -en "\033[0;31m"
  echo "🔴 FAILED"
  echo -en "\033[0m"
}

function display_test_suite() {
  local suite_name="$1"
  echo
  echo -en "\033[0;35m"
  echo 🧪 "$suite_name"
  echo "<--------------------------------------------------------------------->"
  echo -en "\033[0m"
} 

function reset_outfile() {
  > $outfile
}

# TODO: Check exit signal
function run_test() {
  local test_name="$1"
  local cmd="$2"
  echo "$test_name"
  reset_outfile
  local mini_output=$(echo -e "$cmd\nexit" | $minishell 2>/dev/null | grep -v "$mini_prompt")
  local mini_outfile=$(cat $outfile)
  reset_outfile
  local bash_output=$(echo -e "$cmd" | bash 2> /dev/null)
  local bash_outfile=$(cat $outfile)
  local leak=$(echo -e "$cmd\nexit" | $valgrind_flags $minishell 2>&1 1>/dev/null)
  if [[ -n "$leak"  && "${leak:0:2}" == "==" ]]; then
    display_leaked
    echo "$leak"
    exit 1
  elif [[ "$mini_output" == "$bash_output" && "$mini_outfile" == "$bash_outfile" ]]; then
    display_passed
  else
    display_failed
    display_diff_output "$mini_output" "$bash_output"
    display_diff_outfile "$mini_outfile" "$mini_outfile"
    exit 1
  fi
}

test_basic() {
  display_test_suite "Basic Tests"
  run_test "echo Hello World" "echo Hello World"
  run_test "cat file" "cat ./minishell.c"
  run_test "invalid cmd" "ekko hello world"
  run_test "full path cat" "/bin/cat ./minishell.c"
}

test_parser() {
  display_test_suite "Parser Test"
  run_test "> at the end" "ls >"
  run_test "< at the end" "ls <"
  run_test ">> at the end" "ls >>"
  run_test "<< at the end" "ls <<"
  run_test "<< without delimiter" "cat <<"
  run_test "> without file" "ls >"
  run_test "< without file" "cat <"
  run_test "empty line" ""
  run_test "expand var" "echo $SHELL"
  run_test "double quotes" "echo \"$USER\""
  run_test "single quotes" "echo '$USER'"
  run_test "multiple quotes" "echo \"Hello '$USER'\""
  run_test "multiple quotes strings" "echo \"Hello\"'There'\"$USER\"'$USER'"
  run_test "multiple strings inside each other" "echo \"Hello '$USER'\" 'Hello \"$USER\"'"
  run_test "quoteception" "echo \"'''\"'\"\"\"\'"
}

test_redirections() {
  display_test_suite "Redirections Tests"
  run_test "redirect output" "ls > $outfile"
  run_test "redirect input" "cat < Makefile"
  run_test "append output" "ls >> $outfile"
  run_test "redirect output to directory" "echo Hello > ."
  run_test "redirect input to incorrect file" "cat < i_do_not_exist.txt"
  run_test "multiple redirects" "cat < Makefile < minishell.c < readline.supp"
  run_test "multiple redirects with error" "cat < Makefile < . < minishell.c"
}

test_pipes() {
  display_test_suite "Test Pipes"
  run_test "multiple pipes" "ls | cat | wc -l"
  run_test "first cmd invalid" "ekko | ls | cat"
  run_test "last cmd invalid" "ls | cat | ekko"
  run_test "redirect input priority" "ls | cat < Makefile | cat > $outfile"
  run_test "redirect output priority" "ls > $outfile | cat"
  run_test "redirect ignoring pipes" "ls > $outfile | cat | cat < Makefile"
}

test_hardmode() {
  display_test_suite "Final Boss"
  run_test "quoted redirection" "echo Hello '>' $outfile" 
}

########### MAIN ###########

# display_banner

reset_outfile
test_basic
test_parser
test_redirections
test_pipes
test_hardmode

# TODO: IDEAS:
# * Put all tests in a list, so you can target a test by passing it's index
# * Test entire section at a time, and you can target sections too
# * Options inside the test script to load sections or specific tests
# * Doomslayer helmet in green at the end if pass on all tests (maybe sections too?)
# * Setup and create config file at the first time, prompting for minishell location
