cmake_minimum_required(VERSION 3.14.0)
project(SimpleHttpServer VERSION 1.0.0)

include(CTest)
enable_testing()

include(FetchContent)

fetchcontent_declare(sharpen GIT_REPOSITORY "http://github.com/KnownSpace/Sharpen" GIT_TAG "1.0.2" SOURCE_DIR "${PROJECT_SOURCE_DIR}/lib/sharpen")
fetchcontent_makeavailable(sharpen)

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
