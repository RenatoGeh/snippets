#!/bin/bash

n=4
if [ ! -z $1 ]; then n=$1; fi
m=$((n*n - 1))

g++ sq_gen.cpp -o sq_gen.out
for i in $(seq 1 $m); do
  mkdir "$i"
  mv sq_gen.out "$i/"
  cd "$i"
  ./sq_gen.out $i
  mv sq_gen.out ../
  cd ..
done

rm sq_gen.out
