cmake_minimum_required(VERSION 3.30)
project(RayTracing VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
include(CTest)

set(gtest_force_shared_crt ON CACHE BOOL "Use shared CRT with GoogleTest" FORCE)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(HelloWorld src/helloworld_ppm.cpp)
add_executable(Main src/main.cpp)

enable_testing()
add_executable(Tests tests/v3_test.cpp)
target_link_libraries(Tests PRIVATE GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(Tests)
