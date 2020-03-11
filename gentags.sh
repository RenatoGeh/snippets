#!/bin/bash

gcc -M -I ~/include "$@" | sed -e 's/[\\ ]/\n/g' | \
        sed -e '/^$/d' -e '/\.o:[ \t]*$/d' | \
        ctags -L - --c++-kinds=+p --fields=+iaS --extras=+q
