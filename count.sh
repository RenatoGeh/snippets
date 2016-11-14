#!/bin/bash

shopt -s nullglob
folds=(*)

max=-1
min=100000
mean=0
n=0

for dir in "${folds[@]}"; do
  if [[ -d "$dir" ]]; then
    m=`ls -1 $dir | wc -l`
    echo "$dir has $m images."
    let n=n+1
    let mean=mean+m
    if [ "$m" -gt "$max" ]; then
      let max=$m
    fi
    if [ "$m" -lt "$min" ]; then
      let min=$m
    fi
  fi
done

let mean=mean/n
echo "Mean: ${mean}"
echo "Max: ${max}"
echo "Min: ${min}"
