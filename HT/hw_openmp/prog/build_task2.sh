#!/bin/bash
g++ -o ./cpf/2.o 2.cpp -fopenmp
./cpf/2.o $1
