#!/bin/bash

# usage: tools/enter_repetition.sh repetition.txt 99 src/experiments/visitor

set -e

sources=$(find $3 -type f -name "*.cpp")

for f in $sources
do
    for i in $(seq 1 $2);
    do
        rand_str=$(tr -dc A-Za-z0-9 < /dev/urandom | head -c 8)
        sed "s/enter random/${rand_str}/g" $3/$1 > $3/$1.tmp;
        sed -i "/enter repetition/r ${3}/${1}.tmp" $f;
        rm $3/$1.tmp
    done
done
