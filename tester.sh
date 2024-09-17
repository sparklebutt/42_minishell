#!/bin/bash

echo ""
echo "🔥----🔥----🔥----🔥----🔥----🔥----🔥----🔥----🔥"
echo "|                                                |"
echo "|         Weclome to our Minishell tester        |"
echo "|                                                |"
echo "🔥----🔥----🔥----🔥----🔥----🔥----🔥----🔥----🔥"
echo ""
# ///////////////////////////////////////////////////////////////

echo "-------------------------------------------------"
echo ""
echo "         Now running simple_commands.sh"
echo "          🔥--🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥"
echo ""
echo "-------------------------------------------------"
./clean_script.sh
bash < scripts/simple_commands.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/simple_commands.sh | grep -v minishell >> test_output.txt
echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""
# ///////////////////////////////////////////////////////////////

echo "-------------------------------------------------"
echo ""
echo "           Now running arguments.sh"
echo "          🔥--🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥--"
echo ""
echo "-------------------------------------------------"
bash < scripts/arguments.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/arguments.sh | grep -v minishell >> test_output.txt
echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""
# ///////////////////////////////////////////////////////////////

echo "-------------------------------------------------"
echo ""
echo "            Now running parsing.sh"
echo "          🔥--🔥--🔥🔥🔥🔥🔥🔥🔥🔥--"
echo ""
echo "-------------------------------------------------"
bash < scripts/parsing.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/parsing.sh | grep -v minishell >> test_output.txt
echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""
# # ///////////////////////////////////////////////////////////////

# echo "-------------------------------------------------"
# echo ""
# echo "          Now running builtin_tests.sh"
# echo "          ----🔥--🔥🔥🔥🔥🔥🔥🔥🔥--"
# echo ""
# echo "-------------------------------------------------"
# # this contains both tests inside for all builtins
# ./scripts/builtin_tests.sh
# echo "-------------------------------------------------"
# ./find_diff.sh
# ./check_leaks.sh
# ./clean_script.sh
# echo ""
# # ///////////////////////////////////////////////////////////////

echo "-------------------------------------------------"
echo ""
echo "             Now running pipes.sh"
echo "          ----🔥--🔥🔥🔥🔥🔥--🔥🔥--"
echo ""
echo "-------------------------------------------------"
bash < scripts/pipes.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/pipes.sh | grep -v minishell >> test_output.txt
echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""
# ///////////////////////////////////////////////////////////////

echo "-------------------------------------------------"
echo ""
echo "            Now running redirections.sh"
echo "          ----🔥--🔥🔥🔥🔥----🔥🔥--"
echo ""
echo "-------------------------------------------------"
bash < scripts/redirections.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/redirections.sh | grep -v minishell >> test_output.txt
echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""
# ///////////////////////////////////////////////////////////////
#
# echo "-------------------------------------------------"
# echo ""
# echo "          Now running env_path.sh"
# echo "          ----🔥--🔥🔥🔥------🔥🔥--"
# echo ""
# echo "-------------------------------------------------"
# bash < scripts/env_path.sh | grep -v minishell >> bash_output.txt
# valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck' --log-file=./valgrind_logs/log.txt ./minishell < scripts/env_path.sh | grep -v minishell >> test_output.txt
# echo "-------------------------------------------------"
# ./find_diff.sh
# ./check_leaks.sh
# ./clean_script.sh
