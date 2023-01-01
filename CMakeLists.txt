cmake_minimum_required(VERSION 3.25)
project(jcc C)

set(CMAKE_C_STANDARD 11)

add_executable(jcc main.c defs.h scan.c data.h decl.h)
