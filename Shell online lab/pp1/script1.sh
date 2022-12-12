#!/bin/bash

[[ $# -eq 0 ]] && {
    echo "Usage script1.sh filename1 filename2 ..."
    exit 0
}

for filename in $*
do
    [[ -e $filename ]] || {
        echo "$filename doesnot exist"
        continue
    }
    [[ -f $filename ]] || {
        echo "$filename is not a regular file"
        continue
    }
    [[ -x $filename ]] && {
        echo "$filename is currently executable"
        echo $(ls -l | grep $filename)
        echo "$filename's executable permission is now changing"
        chmod -x $filename
        echo $(ls -l | grep $filename)
        echo "$filename is currently not executable"
    } || {
        echo $(ls -l | grep $filename)
    }
done
