cmake_minimum_required(VERSION 3.22)

set( CMAKE_CXX_FLAGS "-std=c++11 -pthread" )
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostartfiles")
SET( CMAKE_VERBOSE_MAKEFILE on )

PROJECT(emptydemo)

set(SOURCES main.cpp connect.cpp basicSockets.cpp secondary.cpp Precompute.cpp tools.cpp)

# foreach(code_src ${SOURCES})
#     message("code_src=${code_src}")
#     get_filename_component(mexecutable ${code_src} NAME_WE)
#     message("name without extension of code_src=${mexecutable}")
#     add_executable(${mexecutable} ${code_src})
#     message("add source file ${code_src} as executable file successfully")
# endforeach(code_src)

add_executable(emptydemo ${SOURCES})
