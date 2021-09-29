cmake_minimum_required (VERSION 3.8)

project (stub C)

add_library(stub SHARED stub.def dllmain.c dinput8/dinput8.c dinput8/dinput8.h)