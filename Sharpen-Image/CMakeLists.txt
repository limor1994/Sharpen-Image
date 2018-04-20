cmake_minimum_required(VERSION 3.8)
project(_5__)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        myfunction.c
        readBMP.c
        readBMP.h
        showBMP.c
        writeBMP.c
        writeBMP.h)

add_executable(_5__ ${SOURCE_FILES})