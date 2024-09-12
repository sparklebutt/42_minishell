#!/bin/bash

echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0        Now running simple_tests.sh          0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind ./minishell < simple_tests.sh | grep -v minishell
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running pipe_tests.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind ./minishell < pipe_tests.sh | grep -v minishell
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running quick_test.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind ./minishell < quick_test.sh | grep -v minishell
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0         Now running quote_test.sh           0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind ./minishell < quotes_test.sh | grep -v minishell
read -n1 -s -r

echo ""
echo "00000000000000000000000000000000000000000000000"
echo "0                                             0"
echo "0       Now running redirect_test.sh          0"
echo "0                                             0"
echo "00000000000000000000000000000000000000000000000"
echo ""
valgrind ./minishell < redirect_test.sh | grep -v minishell
read -n1 -s -r
