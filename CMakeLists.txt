cmake_minimum_required(VERSION 3.17)
project(remote-procedure-call-service)

set(CMAKE_CXX_STANDARD 14)
set(CC "gcc")
set(CFLAGS "-fsanitize=signed-integer-overflow -fsanitize=undefined -g -std=gnu99 -O2 -Wall -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow")


add_executable(backend backend.c a1_lib.c message.h)
add_executable(frontend frontend.c a1_lib.c message.h)