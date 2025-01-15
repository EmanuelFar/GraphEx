#!/bin/bash

INPUT_DIR="infiles"

g++ main.cpp -o test
./test "$INPUT_DIR"/*.dat
