cmake_minimum_required(VERSION 3.15)
project(HashDict)

# Define C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(HashDict_lib STATIC HashDict.cpp)
add_executable(main main.cpp)
target_link_libraries(main PRIVATE HashDict_lib)