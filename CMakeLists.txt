cmake_minimum_required(VERSION 3.10)

project(adt-creator VERSION 1.0)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB sources
     "*.h"
     "*.cpp"
)

add_executable(adt-creator ${sources})
target_include_directories(adt-creator PUBLIC "${PROJECT_SOURCE_DIR}")
