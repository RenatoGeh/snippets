#!/bin/bash

longest=0
for word in $(<$1)
do
    len=${#word}
    if (( len > longest ))
    then
        longest=$len
        longword=$word
    fi
done
printf 'The longest word is %s and its length is %d.\n' "$longword" "$longest"
