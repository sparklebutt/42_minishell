#!/bin/bash

/bin/date +%Y-%m-%d

/bin/echo Hello

/bin/cat ./Makefile

/bin/mkdir test_files/new_folder

/bin/touch test_files/old_file

/bin/rm test_files/old_file

/bin/touch test_files/new_file.txt

/bin/chmod 644 test_files/new_file.txt

# /bin/hostname -I

# /bin/find / -name filename

/bin/mv test_files/new_file.txt test_files/newer_file.txt

/bin/cp test_files/newer_file.txt test_files/file2.txt

/bin/rm test_files/newer_file.txt test_files/file2.txt
