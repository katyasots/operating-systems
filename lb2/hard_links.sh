#!/bin/bash

if [ $# -lt 1 ]
then
echo $0: error
else
filename=$1
inode=$(ls -i $filename | cut -d ' ' -f 1 | tr -d " ")
tmp=$(ls -lRi /home/katya | grep $inode)
fi

echo $tmp
