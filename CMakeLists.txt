cmake_minimum_required(VERSION 3.10.2)
project(BSTest)

find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(${Boost_INCLUDE_DIR})

add_executable(BST_client client.cpp)
add_executable(BST_server server.cpp)
target_link_libraries(BST_client ${Boost_LIBRARIES})
target_link_libraries(BST_server ${Boost_LIBRARIES})