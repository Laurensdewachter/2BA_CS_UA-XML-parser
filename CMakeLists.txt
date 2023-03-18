cmake_minimum_required(VERSION 3.24)
project(Parser)

set(CMAKE_CXX_STANDARD 17)

add_executable(parser main.cpp Parser.cpp Tokenizer.cpp)
