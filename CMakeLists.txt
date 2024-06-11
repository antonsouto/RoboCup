cmake_minimum_required(VERSION 3.20)

project(Player)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Set source files
set(SOURCE_FILES
    main.cpp
    # stringutils.cpp 
    # parsemessages.cpp
    # parseseemessages.cpp
    # parsehearmessages.cpp
    # types.cpp
    # tictoc.cpp 
)

add_executable(Player ${SOURCE_FILES})


