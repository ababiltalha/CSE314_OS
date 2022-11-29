#!/bin/bash

[[ $# -gt 1 ]] && exit 1

if (( $# == 0 ))
then
    n=100
else
    n=$1
fi

touch trial.csv
touch out.txt
touch temp.txt
./Submissions/1805121/1805121.sh > out.txt

diff out.txt AcceptedOutput.txt > temp.txt
firstFile=$( grep -c "^<" temp.txt )
secondFile=$( grep -c "^>" temp.txt )
echo 1805121,$((100-5*( $firstFile + $secondFile ) )) >> trial.csv


echo $n


