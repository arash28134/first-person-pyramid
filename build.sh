#!/bin/bash

cmake -S . -B build
cd build/
make

if [[ $* == *--r* ]]
then
    ./first_person_pyramid
fi