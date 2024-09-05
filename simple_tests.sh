#!/bin/bash

#test simple commands 
#---------------------------------

ls
ls -l
pwd
echo "test this, this is the test"
cat | cat | ls
#creating file.txt
touch file.txt
#removing file.txt
rm file.txt
export VARIABLE=wwwweeeeeewwwwwwoooooooooowwwweeeeewwwoooooo
env
echo $VARIABLE
unset VARIABLE
#end of simple commands test
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#creating dir.dir
#mkdir dir.dir
#removing dir.dir
#rm -R dir.dir
