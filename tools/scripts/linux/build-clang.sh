#!/bin/bash

cmake -S/source -B/build/clang -DCMAKE_BUILD_TYPE=Release -G Ninja \
  -DCMAKE_C_COMPILER=clang                                         \
  -DCMAKE_CXX_COMPILER=clang++                                     \
  -DCMAKE_CXX_FLAGS="-Wall -Wextra -Werror"                     && \
cmake --build /build/clang
