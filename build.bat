@echo off

EM - Build
mkdir bin 2> NUL
pushd bin
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -GNinja -DCMAKE_CXX_FLAGS_RELEASE="-O2" ..
cmake --build . --target mathexpr
popd