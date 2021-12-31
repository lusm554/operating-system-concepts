#!/bin/bash

clang FileCopy.c

# 'strace' for linux
sudo dtruss ./a.out test.txt result.txt
