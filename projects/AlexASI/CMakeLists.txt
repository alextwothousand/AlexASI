# CMakeList.txt : CMake project for AlexASI, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (AlexASI SHARED AlexASI.c AlexASI.h)

# TODO: Add tests and install targets if needed.
