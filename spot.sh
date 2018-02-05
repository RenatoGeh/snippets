#!/bin/bash

# Prints spotify track information.

s=$(playerctl -p spotify status)
if [ "$s" == "Playing" ]; then
  title=$(playerctl -p spotify metadata title)
  artist=$(playerctl -p spotify metadata artist)
  album=$(playerctl -p spotify metadata album)
  line="{$title} by ($artist) on [$album] -- "
  ctime=$(date +%s)
  len="${#line}"
  let s=ctime%len
  let n=len-1
  t_line=""
  for i in `seq $s $n`; do
    t_line=${t_line}${line:i:1}
  done
  let m=s-1
  for i in `seq 0 $m`; do
    t_line=${t_line}${line:i:1}
  done
  #echo "${f_line}${s_line}"
  echo "$t_line"
fi
