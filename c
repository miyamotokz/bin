#!/bin/sh

#c main.cppまたはmain.cをコンパイル&実行
#c "文字列" 文字列/main.cppを作成

S=$1

if [ "$S" = "" ] ; then
    #引数なし（実行）
    if [ -e "main.cpp" ];then
        g++ -o main.o main.cpp
        ./main.o
    else
        echo main.cpp not found
    fi
else
    #引数あり（作成）
    if [ -d ./$1 ];then
        echo $1 is already exists
    else
        mkdir $1
        cp ~/bin/skeleton.cpp ./$1/main.cpp
        echo created $1
    fi

fi
