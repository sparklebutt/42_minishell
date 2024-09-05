#!/bin/bash
./minishell < simple_tests.sh
read -n1 -s -r
./minishell < test_scripts.sh
read -n1 -s -r
