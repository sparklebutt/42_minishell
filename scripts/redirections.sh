ls -l | grep .txt > test_files/out

cat test_files/out

echo "helloooooooooo" >> test_files/out

cat < test_files/out

cat < test_files/meow.txt > test_files/out

cat test_files/out
