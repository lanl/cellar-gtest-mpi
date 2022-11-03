cmake_minimum_required(VERSION 3.10)
project(gtest-mpi-lib LANGUAGES CXX)

file(GLOB SOURCES src/*.cpp)

add_library(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} PUBLIC GTest::GTest MPI::MPI_CXX)

install(TARGETS gtest-mpi-lib
    EXPORT gtest-mpi-libTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
    BUNDLE DESTINATION bin)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/" DESTINATION include)
install(EXPORT gtest-mpi-libTargets DESTINATION lib/cmake/gtest-mpi)