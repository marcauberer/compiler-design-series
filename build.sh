#!/bin/sh
mkdir bin

# Build
(
  cd ./bin || exit
  cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -GNinja -DCMAKE_CXX_FLAGS_RELEASE="-O2" ..
  cmake --build . --target mathexpr
)