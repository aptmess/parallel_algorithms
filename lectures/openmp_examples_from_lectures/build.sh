#!/bin/bash

if [ -z $3 ]; then
    echo Run not in parallel
    g++ -o ./cpf/$1 $2
else
    echo Run in parallel
    g++ -o ./cpf/$1 -fopenmp $2
fi

./cpf/$1
