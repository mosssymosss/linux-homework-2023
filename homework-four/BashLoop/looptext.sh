#!/bin/bash

if [ $# -ne 2 ] ; then
	echo "wrong args"
	exit 1
fi

num=$1
text=$2

for ((i=1; i<=num; ++i)); do
	echo "$text $i" > "file_$i.txt"
done



