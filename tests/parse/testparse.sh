#!/bin/sh

for i in `find . -not -name "*.cc" -not -name "*.txt"`; do
    ./testparse $i 2>/dev/null;
    if [ $? -eq 0 ]; then
        printf '%s%*s\n' $f $((`tput cols` - ${#f})) "\e[00;32mKO\e[00m";
    else
        printf '%s%*s\n' $f $((`tput cols` - ${#f})) "$i \e[00;31mKO\e[00m";
    fi;
done
