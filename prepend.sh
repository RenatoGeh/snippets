#!/bin/bash

if [ $# -lt 2 ]; then
  echo "Prepends contents of first file to all remaining files."
  echo "Usage: $0 f0 [f1 f2 ...]"
  echo "  f0    - file whose contents will be prepended"
  echo "  [...] - list of files to prepend to"
  exit 1
fi

head=`cat $1`
files=($@)
outs=${files[@]:1:${#files[@]}}

for f in ${outs[@]}; do
  echo "Prepending contents from $1 to $f..."
  printf "%s\n\n" "$head" | cat - $f > /tmp/_tmp.txt && mv /tmp/_tmp.txt $f
  echo "Done."
done
