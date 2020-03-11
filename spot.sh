#!/bin/bash

MAX_LEN=70

# Prints spotify track information.

skipped=0

s=$(playerctl -p spotify status)
if [ "$s" == "Playing" ]; then
  title=$(playerctl -p spotify metadata title)
  artist=$(playerctl -p spotify metadata artist)
  album=$(playerctl -p spotify metadata album)
  line="{$title} by ($artist) in [$album] -- "
  ctime=$(date +%s)
  len="${#line}"
  if [ "$len" -lt "$MAX_LEN" ]; then
    echo "{$title} by ($artist) on [$album]"
  else
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

  if [ "$title" == "Advertisement" ] || [ "$title" == "Spotify" ]; then
    if (( ctime % 2 == 0 )) && (( skipped == 0 )); then
      /usr/local/bin/spot-next
      let skipped=1
    fi
  else
    let skipped=0
  fi
fi
