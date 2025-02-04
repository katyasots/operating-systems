#!/bin/bash

#размер директории
size=$(du -hs $1)
echo "размер директории:" $size

#создаем новые файлы txt
for i in {1..50}
do
	name=$1/$i.txt
	>$name
	#запись информации (для придания файлам "веса")
	echo "Sots Ekateryna Andreevna 2384" >> $name
	mkdir $1/$i
done

#размер директории после изменений
size=$(du -hs $1)
echo "размер директории после добавления файлов:" $size

#удаляем некоторые файлы
for i in {27..47}
do
	name=$1/$i.txt
	rm -rf $name $1/$i
done

#размер директории после изменений
size=$(du -hs $1)
echo "размер директории после удаления файлов:" $size
