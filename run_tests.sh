#!/bin/bash

echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0        Now running simple_tests.sh          0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
./minishell < simple_tests.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running pipe_tests.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
./minishell < pipe_tests.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running quick_test.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
./minishell < quick_test.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running quote_test.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
./minishell < quotes_test.sh | grep -v minishell >> test_output.txt
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0       Now running redirect_test.sh          0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
./minishell < redirect_test.sh | grep -v minishell >> test_output.txt
read -n1 -s -r


echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running env_tests.sh            0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
./minishell < env_test.sh | grep -v minishell
read -n1 -s -r