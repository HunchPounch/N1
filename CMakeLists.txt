cmake_minimum_required(VERSION 2.8)

project(N1)

set(N1_src test.cpp CParser.cpp main.cpp)
set(N1_hdr CParser.h test.h)

add_executable(${PROJECT_NAME} ${N1_src} ${N1_hdr})