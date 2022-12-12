#!/bin/bash

line=$1
str=$2

# for loop through files in current directory
for filename in $(ls)
do
    # check if file is a regular file
    [[ -f $filename ]] && {
        # check if file is a text file
        [[ $(file $filename | grep -c "txt") -eq 1 ]] && {
            # check if file contains the string
            [[ $(grep --with-filename --line-number $str $filename) ]] && {
                rm $filename
                continue
            }
        }
    }
done