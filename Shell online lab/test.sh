#!/bin/bash

echo "enter a value"
read val
echo $val

# exp=12

# if [ $val -eq $exp ] ; then
# echo "12 equals 12"
# else
# echo "$val not equals 12"
# fi

for i in {1805121..$val}
do
    echo $i
done

for i in $(seq 1 2 20)
do
   echo "Welcome $i times"
done
