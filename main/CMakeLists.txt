cmake_minimum_required(VERSION 3.10)
project(gtest-mpi-main LANGUAGES CXX)

file(GLOB SOURCES src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gtest-mpi-lib)

install(TARGETS gtest-mpi-main
    EXPORT gtest-mpi-mainTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
    BUNDLE DESTINATION bin)

install(EXPORT gtest-mpi-mainTargets DESTINATION lib/cmake/gtest-mpi)