#!/bin/bash

cd parse;
echo -e "\033[1;35m-- Parser Test Suite --\033[0m"
./testparse.sh;

#echo "-- Pretty-Printer --"
#./testpretty-printer.sh
cd ..;
