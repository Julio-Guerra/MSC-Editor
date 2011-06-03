#!/bin/bash

total=0;
passed=0;
for i in `find ./files/ -not -name "*.cc" -not -name "*.txt" -not -name "*.sh"`; do
    echo -n "$i ";
    ./../../build/tests/parse/testparse $i;
    if [ $? -eq 0 ]; then
        echo -e "\e[00;32mOK\e[00m";
        passed=$(($passed + 1));
    else
        echo -e "\e[00;31mKO\e[00m";
    fi;
    total=$(($total + 1));
done;

if [ $passed -eq $total ]; then
  echo -en "\e[00;32m";
else
    echo -en "\e[00;31m";
fi;
echo "-- Summary : $(($passed * 100 / $total))% passed | $passed / $total";
