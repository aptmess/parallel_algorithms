#!/bin/bash
mpic++ -o ./mp/$2 $1
mpirun --oversubscribe -np $3 ./mp/$2
