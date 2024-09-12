#!/bin/bash

# Run the test script with bash and capture the output
#bash < simple_tests.sh > bash_output.txt

# Run the test script with minishell and capture the output
#./minishell < simple_tests.sh > minishell_output.txt

# Compare the outputs using diff
if diff bash_output.txt test_output.txt > /dev/null; 
	then
		echo "Both outputs match!"
else
	echo "Outputs differ!"
	echo "Differences:"
	diff bash_output.txt test_output.txt
fi