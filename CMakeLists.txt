cmake_minimum_required(VERSION 3.30)
project(RayTracing VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(HelloWorld src/helloworld_ppm.cpp)
add_executable(Main src/main.cpp)