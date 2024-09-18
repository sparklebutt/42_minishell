grep mew <./test_files/meow.txt

grep hi "world!" <         ./test_files/meow.txt

echo "HELLO THERE"        < ./test_files/meow.txt nope nope

grep hi <./test_files/big_file <./test_files/meow.txt

echo <"./test_files/meow.txt" "codeing       42"

cat <"./test_files/file name with spaces"

cat <./test_files/big_file ./test_files/out

cat <"1""2""3""4""5"

echo <"./test_files/out" <missing <"./test_files/out"

echo <missing <"./test_files/meow.txt" <missing

cat <"./test_files/meow.txt"

echo <"./test_files/big_file" | cat <"./test_files/meow.txt"

echo <"./test_files/big_file" | cat "./test_files/meow.txt"

echo <"./test_files/big_file" | echo <"./test_files/meow.txt"

echo hi | cat <"./test_files/meow.txt"

echo hi | cat "./test_files/meow.txt"

cat <"./test_files/meow.txt" | echo hi

cat <"./test_files/meow.txt" | grep hello

cat <"./test_files/big_file" | echo hi

cat <missing

cat <missing | cat

cat <missing | echo oi

cat <missing | cat <"./test_files/meow.txt"

echo <123 <456 hi | echo 42

ls >./outfiles/out01

ls >         ./outfiles/out01

echo hi >         ./outfiles/out01 bye

ls >./outfiles/out01 >./outfiles/out02

chmod 0 test_files/no_perms

ls >./outfiles/out01 >./test_files/no_perms

ls >"./outfiles/outfile with spaces"

ls >"./outfiles/outfile""1""2""3""4""5"

ls >"./outfiles/out01" >./test_files/no_perms >"./outfiles/out02"

ls >./test_files/no_perms >"./outfiles/out01" >./test_files/no_perms

cat <"./test_files/meow.txt" >"./outfiles/out01"

echo hi >./outfiles/out01 | echo bye

echo hi >./outfiles/out01 >./outfiles/out02 | echo bye

echo hi | echo >./outfiles/out01 bye

echo hi | echo bye >./outfiles/out01 >./outfiles/out02

echo hi >./outfiles/out01 | echo bye >./outfiles/out02

echo hi >./outfiles/out01 >./test_files/no_perms | echo bye

echo hi >./test_files/no_perms | echo bye

echo hi >./test_files/no_perms >./outfiles/out01 | echo bye

echo hi | echo bye >./test_files/no_perms

echo hi | >./outfiles/out01 echo bye >./test_files/no_perms

echo hi | echo bye >./test_files/no_perms >./outfiles/out01

cat <"./test_files/meow.txt" >./test_files/no_perms

cat >./test_files/no_perms <"./test_files/meow.txt"

cat <missing >./outfiles/out01

cat >./outfiles/out01 <missing

cat <missing >./test_files/no_perms

cat >./test_files/no_perms <missing

cat >./outfiles/out01 <missing >./test_files/no_perms

ls >>./outfiles/out01

ls >>      ./outfiles/out01

ls >>./outfiles/out01 >./outfiles/out01

ls >./outfiles/out01 >>./outfiles/out01

ls >./outfiles/out01 >>./outfiles/out01 >./outfiles/out02

ls >>./outfiles/out01 >>./outfiles/out02

ls >>./test_files/no_perms

ls >>./test_files/no_perms >>./outfiles/out01

ls >>./outfiles/out01 >>./test_files/no_perms

ls >./outfiles/out01 >>./test_files/no_perms >>./outfiles/out02

ls <missing >>./test_files/no_perms >>./outfiles/out02

ls >>./test_files/no_perms >>./outfiles/out02 <missing

echo hi >>./outfiles/out01 | echo bye

echo hi >>./outfiles/out01 >>./outfiles/out02 | echo bye

echo hi | echo >>./outfiles/out01 bye

echo hi | echo bye >>./outfiles/out01 >>./outfiles/out02

echo hi >>./outfiles/out01 | echo bye >>./outfiles/out02

echo hi >>./test_files/no_perms | echo bye

echo hi >>./test_files/no_perms >./outfiles/out01 | echo bye

echo hi | echo bye >>./test_files/no_perms

echo hi | echo >>./outfiles/out01 bye >./test_files/no_perms

cat <minishell.h>./outfiles/outfile

cat <minishell.h|ls

chmod 777 test_files/no_perms