#!/bin/bash

if [ "$#" -ne 2 ]; then
  echo "Recursively diffs same name files from different paths."
  echo "Usage: $0 path expr"
  echo "  path - path to recursively search remote files"
  echo "  expr - expression to find files (e.g. *.cpp to find all C++ source code files)"
fi

files=`find . -type f -name "$2"`
for f in ${files[@]}; do
  lf=`echo "$f" | cut -c3-`
  rf="$1/$lf"
  echo "$lf <-> $rf"
  nvim -d "$lf" "$rf"
done
