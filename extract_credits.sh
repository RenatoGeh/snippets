#!/bin/bash

if [ $# -ne 2 ]; then
  echo "Extracts course credit information from University of Sao Paulo's course webpage."
  echo "Usage: $0 in out"
  echo "  in  - file containing a list of courses to be extracted"
  echo "  out - output file"
  exit 1
fi

in_data=($(cat $1))
out_f="$2"

tmp_f="/tmp/_webpage_contents.txt"

a_total=0
t_total=0
total=0

:> "$out_f"
for d in ${in_data[@]}; do
  echo "Extracting credit listing for: $d..."
  lynx -dump -nolist -force_html "https://uspdigital.usp.br/jupiterweb/obterDisciplina?sgldis=$d" > "$tmp_f"
  a_u=($(awk '/ditos Aula/' $tmp_f))
  a=${a_u[2]}
  t_u=($(awk '/ditos Trabalho/' $tmp_f))
  t=${t_u[2]}
  let a_total=a_total+a
  let t_total=t_total+t
  printf "%s %2d %2d\n" $d $a $t >> "$out_f"
  printf "Credits:\n  Theory: %d\n  Practical: %d\n\n" $a $t
done
let total=a_total+t_total
