
#!/bin/bash

#quotes testing
#----------------------

echo ""'$HOME'""
echo ""'"$HOME"'"" 
echo "'"""$HOME"""'"
echo ''""'"$HOME"'""''
echo "''""'"$HOME"'""''"
echo '""'$HOME'""'
echo $"USER"
echo "$""USER"
echo ""$""USER""
echo '$'USER
echo $HOME''

cat "meow.txt"
cat "'meow.txt'"

export TEST1=wwweeeeeeeee
export TEST2=wwwooooooooooo
echo "$TEST1$TEST2"
echo '$TEST1$TEST2'
echo "$HOME is where the heart is"
