#!/bin/bash

for j in 8 4 2;
do
    for k in 10 2 1;
    do
        for i in $(seq 1 $j);
        do
            python processo.py $i $j $k $1 &
        done
        wait
        echo "Terminamos a execução mais"
    done
done