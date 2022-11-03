#include <gtest/gtest.h>
#include <mpi.h>

TEST(GTestMPI, Basic) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bool is_root = rank == 0;

    bool is_anyone_root = false;
    MPI_Allreduce(&is_root, &is_anyone_root, 1, MPI_CXX_BOOL, MPI_LOR, MPI_COMM_WORLD);

    ASSERT_TRUE(is_anyone_root);
}