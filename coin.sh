#!/bin/bash

shopt -s nullglob
folds=(*)

ntrain=25
ntest=5

if [[ "$1" == "clean" ]]; then
  rm */test -r
  rm */train -r
  exit 0
elif [[ "$1" == "count" ]]; then
  echo "All test dirs should be ${ntest}."
  for d in */; do
    ls "$d/test" -1 | wc -l
  done
  echo "All train dirs should be ${ntrain}."
  for d in */; do
    ls "$d/train" -1 | wc -l
  done
  exit 0
fi

for dir in "${folds[@]}"; do
  if [[ -d "$dir" ]]; then
    n=0
    for f in ${dir}/*; do
      if [[ -f $f && $f == *.pgm ]]; then
        filename=$(basename "$f")
        base="${filename%.*}"
        pgms[n]="${base}.pgm"
        let n=n+1
      fi
    done
    for i in `seq 0 $(( n - 1 ))`; do
      p=$(( RANDOM % n ))
      q=$(( RANDOM % n ))
      tmp=${pgms[p]}
      pgms[p]=${pgms[q]}
      pgms[q]=$tmp
    done
    mkdir -p "${dir}/train"
    mkdir -p "${dir}/test"
    itrain=0
    itest=0
    for i in `seq 0 $(( n - 1 ))`; do
      coin=$(( RANDOM % 2 ))
      echo "Tossing coin for ${dir}/${pgms[i]}."
      if [ "$coin" -eq "0" ] && [ "$itrain" -lt "$ntrain" ]; then
        cp "${dir}/${pgms[i]}" "${dir}/train/${pgms[i]}"
        let itrain=itrain+1
      elif [ "$itest" -lt "$ntest" ]; then
        cp "${dir}/${pgms[i]}" "${dir}/test/${pgms[i]}"
        let itest=itest+1
      elif [ "$itrain" -lt "$ntrain" ]; then
        cp "${dir}/${pgms[i]}" "${dir}/train/${pgms[i]}"
        let itrain=itrain+1
      else
        break
      fi
    done
  fi
done
