# 声明要求的cmake最低版本
cmake_minimum_required(VERSION 2.8)

# 声明一个cmake工程
project(HelloSLAM)

# 添加一个可执行程序
add_executable(helloSLAM helloSLAM.cpp)
add_executable(useHello useHello.cpp)
add_library(hello_shared SHARED libHelloSLAM.cpp)
target_link_libraries(useHello hello_shared)
