cmake_minimum_required(VERSION 3.14.0)

set(SHARPEN_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/sharpen/include")

include_directories(${SHARPEN_INCLUDE_DIR})

file(GLOB_RECURSE src "${PROJECT_SOURCE_DIR}/src" "*.h" "*.hpp" "*.cpp" "*.cc")

add_executable(SimpleHttpServer ${src})

target_link_libraries(SimpleHttpServer sharpen::sharpen)