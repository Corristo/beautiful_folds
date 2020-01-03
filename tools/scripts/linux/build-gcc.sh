#!/bin/bash

mkdir -p /build/gcc
cmake -H/source -B/build/gcc -DCMAKE_BUILD_TYPE=Release -G Ninja \
  -DCMAKE_C_COMPILER=gcc                                         \
  -DCMAKE_CXX_COMPILER=g++                                       \
  -DCMAKE_CXX_FLAGS="-Wall -Wextra -Werror"                   && \
cmake --build /build/gcc
