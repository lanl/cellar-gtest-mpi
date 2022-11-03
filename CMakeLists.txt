cmake_minimum_required(VERSION 3.10)
project(gtest-mpi VERSION 0.1.1 LANGUAGES CXX)

find_package(GTest REQUIRED)
find_package(MPI REQUIRED)

option(
    GTEST_MPI_TESTING
    "Enables testing for gtest-mpi. Should not be enabled when just configuring
    for install."
    ON)

add_subdirectory(lib)
add_subdirectory(main)

if (GTEST_MPI_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()

include(cmake/install.cmake)