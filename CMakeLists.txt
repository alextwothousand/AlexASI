# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_C_STANDARD 11)

project (AlexASI C)

# Global configuration.
add_compile_definitions(UNICODE _UNICODE)

# Include sub-projects.
add_subdirectory (projects/AlexASI)
add_subdirectory(projects/stub)