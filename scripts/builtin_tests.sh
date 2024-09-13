#!/bin/bash

bash < script/redirect_test.sh | grep -v minishell >> bash_output.txt
valgrind --leak-check=full --gen-suppressions=yes --log-file=./valgrind_logs/log.txt ./minishell < script/redirect_test.sh | grep -v minishell >> test_output.txt

./check_leaks.sh
# ///////////////////////////////////////////////////////////////
echo "-------------------------------------------------"
echo ""
echo "          Now running redirect_test.sh"
echo "          🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥"
echo ""
echo "-------------------------------------------------"


echo "-------------------------------------------------"
./find_diff.sh
./check_leaks.sh
./clean_script.sh
echo ""
# ////////////////////////////////////////////////////////////////