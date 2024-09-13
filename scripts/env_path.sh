#!/bin/bash

env | grep "^PATH=.*:/bin:.*"
echo ""

unset PATH
env
#"unset PATH"

export PATH
env
#"export PATH"

export PATH=
env
#"export PATH="

export PATH=/a
env
#"export PATH=/a"

export PATH=/bin/env
env
#"export PATH=/bin/env"

export PATH=/usr/bin:/bin/env:
env
#"export PATH=/bin/bin:/bin/env:"

export PATH=/bin/
env | grep "^PATH=.*:/bin:.*"

export PATH=/bins
env
#"export PATH=/bin/bin:/bins:/bin/env:aaaaaaa"

export PATH=aaaaa:/bin:
env | grep "^PATH=.*:/bin:.*"

export PATH=aa::/bin:a:
env | grep "^PATH=.*:/bin:.*"

export PATH=/bin:aaaaa:
env | grep "^PATH=.*:/bin:.*"

unset PATH
export =/bin
env
#"unset PATH"
#"export =/bin"