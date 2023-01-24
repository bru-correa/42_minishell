#!/bin/bash

minishell="./minishell"

function displayBanner() {
  echo -e "\033[0;31m"
  cat ./tests/banner.txt
  echo -e "\033[5;31m"
  echo -e "                    Press ENTER to continue"
  echo -e "\033[0m"
  read END
  clear
}

function nextTest() {
  echo -e "\033[0;35m"
  echo
  echo "                                Press Enter to continue -------------->"
  echo -e "\033[0m"
  read END
  clear
}

function displayTestName() {
  echo -e "\033[0;35m"
  echo 🧪 "$1"
  echo "<--------------------------------------------------------------------->"
  echo -e "\033[0m"
} 

function test() {
  displayTestName "$1"
  echo -e "$2" | $minishell
  nextTest
}

function runTest() {
  displayTestName "$1"
  echo -e "$2\nexit" | $minishell
  nextTest
}

function displaySection() {
  echo -e "\033[0;31m"
  echo "########## 😈 $1 😈 ##########"
  echo -e "\033[0m"
  nextTest
}

########### MAIN ###########

displayBanner

runTest "echo Hello World" "echo Hello World"
runTest "cat file" "cat ./minishell.c"
runTest "empty line" ""
runTest "invalid cmd" "ekko hello world"
runTest "full path cat" "/bin/cat ./minishell.c"
# runTest "test pipe" "ls | wc -l"
# runTest "open file without cmd" "> file.txt"
# runTest "mini paradox" "$minishell"


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
