cmake_minimum_required(VERSION 3.6)
project(multiChatSystem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    CMakeLists.txt
    main.cpp client.cpp)

add_executable(server main.cpp)
add_executable(client client.cpp)