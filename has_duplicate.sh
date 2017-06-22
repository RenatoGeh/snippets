#!/bin/bash

for f in "$@"; do
  for g in "$@"; do
    if [ "$f" != "$g" ]; then
      diff "$f" "$g" > /dev/null
      retval=$?
      if [ $retval -eq 0 ]; then
        echo "Has duplicate: $f and $g"
        exit 1
      fi
    fi
  done
done

echo "No duplicates."
exit 0
