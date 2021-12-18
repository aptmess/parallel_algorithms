#!/bin/bash
mpic++ -o ./cpf/$2 $1
mpirun --oversubscribe -np $3 ./cpf/$2
