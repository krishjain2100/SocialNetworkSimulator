#!/usr/bin/env bash
# compile.sh — Compile and run SocialNet project
#  chmod +x compile.sh && ./compile.sh

set -e  
echo "Compiling SocialNet..."
g++ -std=c++23 -O2 -Wall -Wextra ./*.cpp -o socialnet
echo "Running SocialNet..."
./socialnet
