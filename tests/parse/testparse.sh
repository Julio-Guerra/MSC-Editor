#!/bin/bash

total96=0;
passed96=0;
total00=0;
passed00=0;

for i in `find ./files/msc96 -name "*.mpr"`; do
    echo -n "$i ";

    ./../../build/tests/parse/testparse 1 $i 2>/dev/null;

    if [ $? -eq 0 ]; then
        echo -e "\e[00;32mOK\e[00m";
        passed96=$(($passed96 + 1));
    else
        echo -e "\e[00;31mKO\e[00m";
    fi;
    total96=$(($total96 + 1));
done;

for i in `find ./files/msc2000 -name "*.mpr"`; do
    echo -n "$i ";

    ./../../build/tests/parse/testparse 0 $i 2>/dev/null;

    if [ $? -eq 0 ]; then
        echo -e "\e[00;32mOK\e[00m";
        passed00=$(($passed00 + 1));
    else
        echo -e "\e[00;31mKO\e[00m";
    fi;
    total00=$(($total00 + 1));
done;

passed=$(($passed00 + $passed96));
total=$(($total00 + $total96));

if [ $passed -eq $total ]; then
  echo -en "\e[00;32m";
else
    echo -en "\e[00;31m";
fi;
echo "** Summary MSC96 : $(($passed96 * 100 / $total96))% passed | $passed96 / $total96";
echo "** Summary MSC2000 : $(($passed00 * 100 / $total00))% passed | $passed00 / $total00";
echo "* Summary : $(($passed * 100 / $total))% passed | $passed / $total";
