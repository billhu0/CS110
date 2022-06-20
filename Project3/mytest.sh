#!/bin/zsh

counter=1

compile_fast () {
    echo "\033[37;44m Compiling \033[0m "
    make fast || { echo "\033[37;41m Compile Error! \033[0m "; exit -1 }
}

compile_all () {
    echo "\033[37;44m Compiling \033[0m "
    make base || { echo "\033[37;41m Compile Error! \033[0m "; exit -1 }
    make fast || { echo "\033[37;41m Compile Error! \033[0m "; exit -1 }
    make check || { echo "\033[37;41m Compile Error! \033[0m "; exit -1 }
}

run_fast() {
    echo -n "\033[37;40m Case $counter \033[0m"
    echo -n "\033[37;46m fast: \033[0m "
    ./gbfloat_fast $1 ./test_fast.jpg $2 $3 $4 $5 $6 || echo "\033[37;41m Runtime Error! \033[0m "
    counter=$[ 1 + $counter ]
}

run_all(){
    echo -n "\033[37;40m Case $counter \033[0m "
    echo -n "\033[37;46m base: \033[0m "
    {./gbfloat_base $1 ./test_base.jpg $2 $3 $4 $5 $6 | tr -d '\n'} || echo -n "\033[37;41m Runtime Error! \033[0m "
    echo -n "\t \033[37;46m fast: \033[0m "

    {./gbfloat_fast $1 ./test_fast.jpg $2 $3 $4 $5 $6 | tr -d '\n'} || echo -n "\033[37;41m Runtime Error! \033[0m "
    echo -n "\t \033[37;46m accuracy: \033[0m "

    {./test_accuracy test_base.jpg test_fast.jpg | tr -d '\n'} # || echo -n "\033[37;41m Wrong Image! \033[0m "
    counter=$[ 1 + $counter]
    echo ""
}

test_without_accuracy () {
    compile_fast

    echo "\033[37;44m Small Original Test \033[0m "
    input_img='test.jpg'
    counter=1
    run_fast $input_img 0.6 -2.0 2.0 79 79
    run_fast $input_img 0.2 -4.0 4.0 421 411
    run_fast $input_img 0.4 -1.0 1.0 999 691
    run_fast $input_img 0.8 -3.0 3.0 1601 799
    run_fast $input_img 0.8 -3.0 3.0 701 601
    run_fast $input_img 0.8 -3.0 3.0 801 789
    run_fast $input_img 0.5 -1.0 1.0 741 1201
    run_fast $input_img 0.4 -1.0 1.0 1921 611

    echo "\033[37;44m Medium Ubuntu Wallpaper Test \033[0m "
    input_img='./ubt.jpg'
    counter=1
    run_fast $input_img 0.6 -2.0 2.0 79 79
    run_fast $input_img 0.2 -4.0 4.0 421 411
    run_fast $input_img 0.4 -1.0 1.0 999 691
    run_fast $input_img 0.8 -3.0 3.0 1601 799
    run_fast $input_img 0.8 -3.0 3.0 701 601
    run_fast $input_img 0.8 -3.0 3.0 801 789
    run_fast $input_img 0.5 -1.0 1.0 741 1201
    run_fast $input_img 0.4 -1.0 1.0 1921 611

    echo "\033[37;44m Big Image Test \033[0m "
    input_img='./test_3_big.jpg'
    counter=1
    run_fast $input_img 0.6 -2.0 2.0 79 79
    run_fast $input_img 0.2 -4.0 4.0 421 411
    run_fast $input_img 0.4 -1.0 1.0 999 691
    run_fast $input_img 0.8 -3.0 3.0 1601 799
    run_fast $input_img 0.8 -3.0 3.0 701 601
    run_fast $input_img 0.8 -3.0 3.0 801 789
    run_fast $input_img 0.5 -1.0 1.0 741 1201
    run_fast $input_img 0.4 -1.0 1.0 1921 611

}

test_with_accuracy () {
    compile_all

    echo "\033[37;44m Small Original Test \033[0m "
    input_img='test.jpg'
    counter=1
    run_all $input_img 0.6 -2.0 2.0 79 79
    run_all $input_img 0.2 -4.0 4.0 421 411
    run_all $input_img 0.4 -1.0 1.0 999 691
    run_all $input_img 0.8 -3.0 3.0 1601 799
    run_all $input_img 0.8 -3.0 3.0 701 601
    run_all $input_img 0.8 -3.0 3.0 801 789
    run_all $input_img 0.5 -1.0 1.0 741 1201
    run_all $input_img 0.4 -1.0 1.0 1921 611

    echo "\033[37;44m Medium Ubuntu Wallpaper Test \033[0m "
    input_img='./ubt.jpg'
    counter=1
    run_all $input_img 0.6 -2.0 2.0 79 79
    run_all $input_img 0.2 -4.0 4.0 421 411
    run_all $input_img 0.4 -1.0 1.0 999 691
    run_all $input_img 0.8 -3.0 3.0 1601 799
    run_all $input_img 0.8 -3.0 3.0 701 601
    run_all $input_img 0.8 -3.0 3.0 801 789
    run_all $input_img 0.5 -1.0 1.0 741 1201
    run_all $input_img 0.4 -1.0 1.0 1921 611

    echo "\033[37;44m Big Image Test \033[0m "
    input_img='./test_3_big.jpg'
    counter=1
    run_all $input_img 0.6 -2.0 2.0 79 79
    run_all $input_img 0.2 -4.0 4.0 421 411
    run_all $input_img 0.4 -1.0 1.0 999 691
    run_all $input_img 0.8 -3.0 3.0 1601 799
    run_all $input_img 0.8 -3.0 3.0 701 601
    run_all $input_img 0.8 -3.0 3.0 801 789
    run_all $input_img 0.5 -1.0 1.0 741 1201
    run_all $input_img 0.4 -1.0 1.0 1921 611
}



if [ $1 -eq 1 ]; then test_without_accuracy; fi
if [ $1 -eq 2 ]; then test_with_accuracy; fi

