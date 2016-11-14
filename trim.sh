#!/bin/bash

shopt -s nullglob
folds=(*)

for dir in "${folds[@]}"; do
  if [[ -d "$dir" ]]; then
    for f in ${dir}/*; do
      if [[ -f $f && $f == *.jpg ]]; then
        filename=$(basename "$f")
        base="${filename%.*}"
        convert "$dir/${base}.jpg" -fuzz 10% -trim +repage "$dir/trim_${base}.jpg"
        echo "Trimmed $dir/${base}.jpg and saved as $dir/trim_${base}.jpg"
      fi
    done
  fi
done
