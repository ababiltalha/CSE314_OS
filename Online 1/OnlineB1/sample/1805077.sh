#!/bin/bash

echo "."

function traverse() {
for file in *
do
    [[ -f "${file}" && "${file}" == *.zip ]] && {
        unzip "${file}" > temp.txt
        rm "${file}"
        rm temp.txt
    }
done

for file in *
do
    [[ ! -d "${file}" ]] && {
        echo "|--${file}"
    } || {
        echo "|  |--${file}"
        cd "${file}"
        traverse
        cd ..
    }
done
}

traverse 