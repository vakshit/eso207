#!/bin/bash

for n in 10 100 5000 25000 50000
do
  echo $n
  gcc random_pairs.c && ./a.out $n
  gcc min_dist.c -lm && ./a.out
  gcc opt_min_dist.c -lm && ./a.out 
  printf "\n\n"
 done
