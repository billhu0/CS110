#!/bin/zsh
# Compiles sizeof.c targeting both 32-bit and 64-bit architectures, using c89 standard.
gcc -Wpedantic -Wall -Wextra -Werror -std=c89 -m32 sizeof.c -o ./sizeof32
gcc -Wpedantic -Wall -Wextra -Werror -std=c89 -m64 sizeof.c -o ./sizeof64
