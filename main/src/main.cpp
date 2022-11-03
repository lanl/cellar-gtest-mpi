#include <gtest-mpi/init.hpp>
#include <gtest/gtest.h>
#include <mpi.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    gtest_mpi::init(&argc, &argv);

    auto exit_code = RUN_ALL_TESTS();

    gtest_mpi::finalize();
    MPI_Finalize();

    return exit_code;
}
