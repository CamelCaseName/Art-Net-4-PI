# CMakeList.txt : CMake project for Art-Net-4-PI, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Art-Net-4-PI")

# Add source to this project's executable.
add_executable (Art-Net-4-PI "Art-Net-4-PI.cpp" "Art-Net-4-PI.h" "Art-Net-Codes.h")

# TODO: Add tests and install targets if needed.
