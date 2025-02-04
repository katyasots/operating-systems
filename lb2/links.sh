#!/bin/bash

filename=$1
ls -lRa /home/katya/ | grep $filename | grep ^l > links.txt

#подсчет кол-ва ссылок:
echo -n "total " >> links.txt
wc -l links.txt | cut -c 1 >> links.txt

com=$(cat links.txt)
echo $com
