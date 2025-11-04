#!/usr/bin/env bash
# compile_io.sh — Compile and run SocialNet with redirected I/O
set -e 
INPUT_FILE="input.txt"
OUTPUT_FILE="output.txt"
echo "Compiling SocialNet..."
g++ -std=c++23 -Wall -Wextra -O2 main.cpp network.cpp user.cpp friends.cpp post.cpp utils.cpp -o socialnet
echo "Running SocialNet with input from '$INPUT_FILE' and output to '$OUTPUT_FILE'..."
./socialnet < "$INPUT_FILE" > "$OUTPUT_FILE"
echo "Execution complete. Output saved to '$OUTPUT_FILE'."
