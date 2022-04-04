#!/bin/bash
#cppファイルテンプレで作る&コンパイルと実行する用

function usage {
  cat <<EOM
Usage: $(basename "$0") [OPTION]...
  $(basename "$0")                  compile&exec ./main.cpp
  $(basename "$0") <dir_name>       create dir_name/main.cpp
  $(basename "$0") -h               Display help
  $(basename "$0") -f <file_name>   create file_name.cpp
  $(basename "$0") -x <file_name>   compile&exec <file_name>.cpp
EOM

  exit 2
}


#コンパイル&実行
function exec {
    if [ -e "$1.cpp" ];then
        g++ -o $1.o $1.cpp
        ./$1.o
        if [ $2 -eq 0 ];then
            rm ./$1.o
            echo removed!
        fi
    else
        echo $1.cpp not found 1>&2
    fi
    exit 1
}

#指定された名前でディレクトリ作成
function create_dir() {
    if [[ $1 =~ ^- ]]; then
        usage
    elif [ -d ./$1 ]; then
        echo $1 is already exists 1>&2
    else
        mkdir $1
        cp ~/bin/skeleton.cpp ./$1/main.cpp
        echo created $1/main.cpp
    fi
    exit 1
}
#指定された名前でファイル作成
function create_file() {
    if [ -e "$1.cpp" ];then
        echo $1 is already exists 1>&2
    else
        cp ~/bin/skeleton.cpp ./$1.cpp
        echo created $1.cpp
    fi
    exit 1
}

FLG_SAVE=0
CREATE=0
EXEC=0
HELP=0
ARG=""
if [ $# -gt 3 ];then
    usage
elif [ $# -eq 0 ];then
    exec main 0
fi

while getopts ":f:x:hs" OPT
    do
    case $OPT in
        s)  FLG_SAVE=1;;
        f)
            CREATE=1;
            ARG=${OPTARG}
        ;;
        x)
            EXEC=1;
            ARG=${OPTARG}
        ;;
        h|'--help'|* )
            HELP=1
        ;;
    esac
done

#$1にファイル名
shift `expr $OPTIND - 1`

#c -h...
if [ "$HELP" = 1 ];then
    usage
# -fxなし c 名前またはc -sのどちらか
elif [ "$CREATE" = "$EXEC" ];then
    if [ $1 ];then
        create_dir $1
    elif [ $FLG_SAVE ];then
        exec main 1
    else
        usage
    fi
#c -x ファイル名指定
elif [ $EXEC = 1  -a $ARG ];then
    exec $ARG $FLG_SAVE
#c -f ファイル名指定
elif [ $CREATE = 1 -a $ARG ];then
    create_file $ARG
#c -s ファイル名指定
elif [$FLG_SAVE = 1 -a $ARG = ""];then
    exec main 1
else
    usage
fi