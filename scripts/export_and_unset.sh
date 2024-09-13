#!/bin/bash

export ATEST=wwwweeeeeeee BTEST=woooooooooooo

echo "$ATEST"'$BTEST'

echo '$ATEST'"$BTEST"

export a=12345 b=678 c=91011 d=121314

echo "'$a'"$b""$c

echo ''$a""$b"'$c'"""$d''

echo "'$a'"$b""heloo""$c

export VARIABLE=wwwweeeeeewwwwwwoooooooooowwwweeeeewwwoooooo

env | grep "^VARIABLE=*"

echo $VARIABLE

unset VARIABLE

export TEST1=wwweeeeeeeee
export TEST2=wwwooooooooooo

echo "$TEST1$TEST2"

echo '$TEST1$TEST2'