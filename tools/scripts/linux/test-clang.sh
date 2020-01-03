#!/bin/bash

__dir=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)
bash __dir/build-clang.sh
cmake --build /build/clang --target check
