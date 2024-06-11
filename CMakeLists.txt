cmake_minimum_required(VERSION 3.20)

project(Ejemplo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set source files
set(SOURCE_FILES
    holaMundo.cpp 
)

add_executable(ejemploPrueba ${SOURCE_FILES})


