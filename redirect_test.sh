#!/bin/bash

ls -l | grep .txt > out
cat out

# append doesn`t work
echo "helloooooooooo" >> out
cat < out

# this also fails
cat < meow.txt > out
cat out