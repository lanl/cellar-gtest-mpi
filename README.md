# Google Test for MPI (gtest-mpi)
This is a support library that helps users write Google Test unit tests that
rely on MPI.

## Features
- Serialized and rank-tagged Google Test output.
- Rank-tagged failure reports.

## Installation
### Spack
[Spack](https://spack.io) is the easiest way to install gtest-mpi. The gtest-mpi
package is available in
[agaspar/spack-repo](https://gitlab.lanl.gov/agaspar/spack-repo). Follow the
README there to use that spack repo. Once the agaspar-spack-repo repo is
installed, installing gtest-mpi is as simple as running:
```
spack install gtest-mpi
```

When you want to use gtest-mpi, run `spack load gtest-mpi` to load it into your
current environment.

### CMake
If you don't want to use spack, you can install gtest-mpi directly using CMake.
gtest-mpi uses CMake, so all of your knowledge of CMake applies. gtest-mpi
has a dependency on Google Test, and uses
[FindGTest.cmake](https://cmake.org/cmake/help/latest/module/FindGTest.html) to
find it. Therefore, in order to install gtest-mpi, you must first have a
working installation of [Google Test](https://github.com/google/googletest/).

Once you've installed Google Test, building and installing gtest-mpi is just
like any other modern CMake package.

```
git clone git@gitlab.lanl.gov:agaspar/gtest-mpi.git
cd gtest-mpi
mkdir build && cd build
cmake ..
make install
```

## Using gtest-mpi
### With CMake
If you don't need any custom startup logic, using gtest-mpi in your own CMake
project is simple:
```cmake
find_package(gtest-mpi 0.1 REQUIRED)

# gtest-mpi-main provides a main function for you
add_executable(my-test mytest.cpp)
target_link_libraries(my-test gtest-mpi-main)
```

Then you can write a Google Test just like you normally would:
```c++
// mytest.cpp
#include <gtest/gtest.h>
#include <mpi.h>

TEST(GTestMPI, Basic) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    bool is_root = rank == 0;

    bool is_anyone_root = false;
    MPI_Allreduce(
        &is_root, &is_anyone_root, 1, MPI_CXX_BOOL, MPI_LOR, MPI_COMM_WORLD);

    ASSERT_TRUE(is_anyone_root);
}
```

If you need to write your own main function, that's also fairly straighforward.
In your CMake project, you link against `gtest-mpi-lib` instead of
`gtest-mpi-main`. Then you must provide your own main function:
```c++
// main.cpp
#include <gtest-mpi/init.hpp>
#include <gtest/gtest.h>
#include <mpi.h>

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    MPI_Init(&argc, &argv);
    gtest_mpi::init(&argc, &argv);

    // Your custom init logic goes here

    int exit_code = RUN_ALL_TESTS();

    // Your custom finalize logic goes here

    gtest_mpi::finalize();
    MPI_Finalize();

    return exit_code;
}
```

### Without CMake
CMake is not required to use gtest-mpi, but it is recommended. If you wish to
use a different build system, then adding `-lgtest-mpi-lib` and (optionally)
`-lgtest-mpi-main` to your link line will work.

## CTest
Here's an example of adding a CTest using gtest-mpi to your CMake file:

```cmake
enable_testing()

add_test(
    NAME my-test
    COMMAND
        ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} 4 ${MPIEXEC_PREFLAGS}
            $<TARGET_FILE:my-test> ${MPIEXEC_POSTFLAGS})
```

These tests can be run using `ctest`.
