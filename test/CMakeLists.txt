cmake_minimum_required(VERSION 3.10)
project(gtest-mpi-test LANGUAGES CXX)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

target_link_libraries(${PROJECT_NAME} PUBLIC gtest-mpi-main)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND
        ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 ${MPIEXEC_PREFLAGS}
            $<TARGET_FILE:${PROJECT_NAME}> ${MPIEXEC_POSTFLAGS})
