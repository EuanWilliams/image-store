#!/bin/bash
mkdir -p build
cd build
# cmake -S . -B . -DCMAKE_CXX_COMPILER='C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\VC\Tools\MSVC\14.16.27023\bin\Hostx64\x64' -DCMAKE_C_COMPILER=C:\msys64\mingw64\bin\gcc
cmake -S . -B . -G "MinGW Makefiles"
make
cd ..
