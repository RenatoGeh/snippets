#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "Reads each line l from f and runs command c with arguments l."
  echo "Usage: $0 f c"
  echo "  f - input file with args"
  echo "  c - command to be run for each line in f"
  exit 1
fi

while read l; do
  echo "Args: $l"
  read -r -a args <<< "$l" && eval "$2" ${l[@]}
done < "$1"
