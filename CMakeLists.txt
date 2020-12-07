cmake_minimum_required(VERSION 3.17)
project(myfork)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(Boost_INCLUDE_DIR /Users/khaled/Desktop/boost_1_71_0)
set(Boost_LIBRARY_DIR /Users/khaled/Desktop/boost_1_71_0/stage/lib)
include_directories(${Boost_INCLUDE_DIR})
find_package(Boost 1.71.0 COMPONENTS filesystem thread iostreams serialization date_time random system REQUIRED)
add_executable(myfork
        main.cpp

        headers/UDPSocket.h
        source/UDPSocket.cpp
        source/ClientSocket.cpp
        source/ServerSocket.cpp
        source/Client.cpp
        source/Server.cpp
        source/Message.cpp
        source/MessageStructure.cpp
        source/myfork.cpp

        headers/ServerSocket.h
        headers/ClientSocket.h
        headers/myfork.h
        headers/Client.h
        headers/Server.h
        headers/Message.h
        headers/MessageStructure.h)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})