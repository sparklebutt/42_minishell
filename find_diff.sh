#!/bin/bash

echo ""
if diff bash_output.txt test_output.txt > /dev/null; 
	then
		echo "           ✅ Both outputs match ✅"
		echo ""
		echo "-------------------------------------------------"
else
	echo "               ❌ Outputs differ ❌"
	echo ""
	echo "Check lines:"
	diff bash_output.txt test_output.txt | grep -v "^[<>]"
	echo "-------------------------------------------------"
	echo ""
	echo "                  Difference:"
	diff -y --width=140 --suppress-common-lines bash_output.txt test_output.txt
	trap 'handle_signal' SIGINT
	echo ""
	read -p $'\e[0;32mPress Enter to continue...\e[0m'
	echo ""
	echo "-------------------------------------------------"
fi