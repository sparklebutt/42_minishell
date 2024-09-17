#!/bin/bash

# ///////////////////////////////////////////////////////////////

echo "-------------------------------------------------"
echo ""
echo "             Now running echo.sh"
echo "        🔥----🔥--🔥🔥🔥🔥🔥--🔥🔥--🔥"
echo ""
echo "-------------------------------------------------"
bash < scripts/echo.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/echo.sh | grep -v minishell >> test_output.txt
echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""

# # ///////////////////////////////////////////////////////////////

echo "-------------------------------------------------"
echo ""
echo "            Now running cd_and_pwd.sh"
echo "        🔥----🔥--🔥🔥🔥🔥----🔥🔥--🔥"
echo ""
echo "-------------------------------------------------"
bash < scripts/cd_and_pwd.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/cd_and_pwd.sh | grep -v minishell >> test_output.txt
echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""

# # ///////////////////////////////////////////////////////////////

# echo "-------------------------------------------------"
# echo ""
# echo "          Now running exit.sh"
# echo "        🔥----🔥--🔥🔥🔥------🔥🔥--🔥"
# echo ""
# echo "-------------------------------------------------"
# bash < scripts/exit.sh | grep -v minishell >> bash_output.txt
# valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/exit.sh | grep -v minishell >> test_output.txt
# echo "-------------------------------------------------"
# ./find_diff.sh
# ./check_leaks.sh
# ./clean_script.sh

# # ///////////////////////////////////////////////////////////////

# echo "-------------------------------------------------"
# echo ""
# echo "             Now running export_and_unset.sh"
# echo "        ------🔥--🔥🔥🔥------🔥🔥--🔥"
# echo ""
# echo "-------------------------------------------------"
# bash < scripts/export_and_unset.sh | grep -v minishell >> bash_output.txt
# valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/export_and_unset.sh | grep -v minishell >> test_output.txt
# echo "-------------------------------------------------"
# ./find_diff.sh
# ./check_leaks.sh
# ./clean_script.sh
# echo ""

# # ///////////////////////////////////////////////////////////////

# echo "-------------------------------------------------"
# echo ""
# echo "            Now running export.sh"
# echo "              FIX THIS ONE"
# echo "        ------🔥--🔥🔥🔥------🔥----🔥"
# echo ""
# echo "-------------------------------------------------"
# bash < scripts/redirections.sh | grep -v minishell >> bash_output.txt
# valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/redirections.sh | grep -v minishell >> test_output.txt
# echo "-------------------------------------------------"
# ./find_diff.sh
# ./check_leaks.sh
# ./clean_script.sh
# echo ""

# # ///////////////////////////////////////////////////////////////

# echo "-------------------------------------------------"
# echo ""
# echo "          Now running unset.sh"
# echo "              FIX THIS ONE"
# echo "        ------🔥--🔥🔥--------🔥----🔥"
# echo ""
# echo "-------------------------------------------------"
# bash < scripts/unset.sh | grep -v minishell >> bash_output.txt
# valgrind --leak-check=full --suppressions=valgrind.supressions --show-leak-kinds=all --track-origins=yes --track-fds=yes --tool=memcheck --log-file=./valgrind_logs/log.txt ./minishell < scripts/unset.sh | grep -v minishell >> test_output.txt
# echo "-------------------------------------------------"
# ./find_diff.sh
# ./check_leaks.sh
# ./clean_script.sh