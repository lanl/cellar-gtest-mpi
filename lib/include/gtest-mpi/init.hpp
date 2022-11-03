#ifndef GTEST_MPI_INIT
#define GTEST_MPI_INIT

namespace gtest_mpi {
void init(int *argc, char ***argv);
void finalize();
} // namespace gtest_mpi

#endif // GTEST_MPI_INIT
