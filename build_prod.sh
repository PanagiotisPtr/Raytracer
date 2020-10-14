#!/bin/bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles"
make all