#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

stats=$(ls -l | grep -o "$1".*)

if [[ -z $stats ]]; then
    echo "Course not found" >&2
    exit 1
fi

directory_name="$1_stat"

if [[ -d $directory_name ]]; then
    rm -rf "$directory_name"
fi

mkdir "$directory_name"

gcc -g -Wall hist.c -o hist.exe

./hist.exe "$stats" > ./"$directory_name"/histogram.txt

gcc -g -Wall mean.c -o mean.exe
gcc -g -Wall median.c -o median.exe
gcc -g -Wall min.c -o min.exe
gcc -g -Wall max.c -o max.exe
mean=$(./mean.exe "$stats")

median=$(./median.exe "$stats")

min=$(./min.exe "$stats")

max=$(./max.exe "$stats")

echo -e "$mean    $median    $min    $max" > ./"$directory_name"/statistics.txt
