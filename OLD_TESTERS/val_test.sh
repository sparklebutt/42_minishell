#!/bin/bash

mkdir valgrind_logs

echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0        Now running simple_tests.sh          0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind --leak-check=full --log-file=./valgrind_logs/log0.txt ./minishell < script/simple_tests.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running pipe_tests.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind --leak-check=full --log-file=./valgrind_logs/log1.txt ./minishell < script/pipe_tests.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running quick_test.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind --leak-check=full --log-file=./valgrind_logs/log2.txt ./minishell < script/quick_test.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running quote_test.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind --leak-check=full --log-file=./valgrind_logs/log3.txt ./minishell < script/quotes_test.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0       Now running redirect_test.sh          0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind --leak-check=full --log-file=./valgrind_logs/log4.txt ./minishell < script/redirect_test.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running env_tests.sh            0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind --leak-check=full --log-file=./valgrind_logs/log5.txt ./minishell < script/env_test.sh
read -n1 -s -r
