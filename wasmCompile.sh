#!/bin/bash

emcc -Os ./cparse/functions.cpp -c -o ./cparse/functions.o
emcc -Os ./cparse/packToken.cpp -c -o ./cparse/packToken.o
emcc -Os ./cparse/shunting-yard.cpp -c -o ./cparse/shunting-yard.o
emcc -Os ./cparse/containers.cpp -c -o ./cparse/containers.o

emcc -Os ./latexParser/sanitize.cpp -c -o ./latexParser/sanitize.o
emcc -Os ./latexParser/solver.cpp -c -o ./latexParser/solver.o

rm -rf ./out
mkdir ./out

emcc -Os --closure 1 -I ./cparse ./latexParser/main.cpp ./cparse/{functions.o,packToken.o,shunting-yard.o,containers.o} ./latexParser/{sanitize.o,solver.o} --bind -o ./out/latexParser.js
