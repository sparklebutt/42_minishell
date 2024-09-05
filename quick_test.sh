
#!/bin/bash

#quickies 1
export ATEST=wwwweeeeeeee BTEST=woooooooooooo
echo "$ATEST"'$BTEST'

echo '$ATEST'"$BTEST"

export a=aaaaaa b=bbbbbbbb
export c=cccccc d=ddddddd

echo "'$a'"$b""$c
echo ''$a""$b"'$c'"""$d''

echo "'$a'"$b""heloo""$c
