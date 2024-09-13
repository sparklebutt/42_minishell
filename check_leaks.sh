#!/bin/bash
echo ""
if [ -e ./valgrind_logs/log.txt ]; then
	cat ./valgrind_logs/log.txt | awk '/LEAK SUMMARY:/,/^$/' | grep -v -E 'HEAP SUMMARY|in use at exit|total heap usage'
	line_count=$(cat ./valgrind_logs/log.txt | awk '/LEAK SUMMARY:/,/^$/' | grep -v -E 'HEAP SUMMARY|in use at exit|total heap usage' | wc -l)
	if [ "$line_count" -gt 30 ]; then
		trap 'handle_signal' SIGINT
		echo ""
		read -p $'\e[0;31mPress Enter to continue...\e[0m'
	fi
else
	echo "             ❌ Log file not found ❌"
	# trap 'handle_signal' SIGINT
	echo ""
	trap 'handle_signal' SIGINT
	echo ""
	read -p $'\e[0;31mPress Enter to continue...\e[0m'
fi
