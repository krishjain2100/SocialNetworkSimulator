#!/usr/bin/env bash
# compile.sh — Compile and run SocialNet project
#  chmod +x compile.sh && ./compile.sh

set -e  
echo "Compiling SocialNet..."
g++ -std=c++23 -Wall -Wextra -O2 main.cpp network.cpp user.cpp friends.cpp post.cpp utils.cpp -o socialnet
echo "Running SocialNet..."
./socialnet
