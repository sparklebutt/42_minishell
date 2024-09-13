cat empty > test_output.txt
cat empty > bash_output.txt

if [ -e ./valgrind_logs/*.txt ]
	then
		rm ./valgrind_logs/*.txt
		touch ./valgrind_logs/log.txt
fi
