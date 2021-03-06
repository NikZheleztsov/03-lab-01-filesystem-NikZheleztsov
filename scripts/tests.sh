#!/usr/bin/env bash

set -e
export GTEST_COLOR=1
CMAKE_LINKER_OPTS="-DCMAKE_EXE_LINKER='-fuse-ld=gold'"
CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD=20"
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='$(pwd)/tools/polly/gcc-pic.cmake'"

cmake -H. -B_builds $CMAKE_OPTS
cmake --build _builds
cmake --build _builds --target test -- ARGS="--verbose"
