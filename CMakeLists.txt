
cmake_minimum_required(VERSION 3.30)
project(hangman)

set(CMAKE_CXX_STANDARD 20)

add_executable(hangman main.cpp wordList.cpp)
