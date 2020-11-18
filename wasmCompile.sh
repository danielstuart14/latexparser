#!/bin/bash

emcc ./cparse/functions.cpp -c -o ./cparse/functions.o
emcc ./cparse/packToken.cpp -c -o ./cparse/packToken.o
emcc ./cparse/shunting-yard.cpp -c -o ./cparse/shunting-yard.o
emcc ./cparse/containers.cpp -c -o ./cparse/containers.o
emcc ./cparse/builtin-features.cpp -c -o ./cparse/builtin-features.o

emcc ./latexParser/sanitize.cpp -c -o ./latexParser/sanitize.o
emcc ./latexParser/solver.cpp -c -o ./latexParser/solver.o

rm -rf ./out
mkdir ./out

emcc -I ./cparse ./latexParser/main.cpp ./cparse/{functions.o,packToken.o,shunting-yard.o,containers.o,builtin-features.o} ./latexParser/{sanitize.o,solver.o} --bind -o ./out/latexParser.js