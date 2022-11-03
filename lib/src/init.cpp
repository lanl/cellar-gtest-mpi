// STL Includes
#include <iostream> // HACK: This must be the first include due to XCode issues.

#include <cstdlib>
#include <memory>

// Third Party Incliudes
#include <gtest-mpi/init.hpp>
#include <gtest/gtest.h>

// Internal Includes
#include "gtest-mpi-listener.hpp"

static std::unique_ptr<MPIMinimalistPrinter> mpi_test_printer;

void gtest_mpi::init(int *argc, char ***argv) {
    (void)argc; // unused
    (void)argv; // unused

    if (mpi_test_printer) {
        std::cerr << "gtest_mpi::init must be called just once!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    testing::AddGlobalTestEnvironment(new MPIEnvironment());

    auto &listeners = testing::UnitTest::GetInstance()->listeners();

    // This removes the "default result printer" which would usually log to stdout.
    delete listeners.Release(listeners.default_result_printer());

    mpi_test_printer = std::make_unique<MPIMinimalistPrinter>();

    listeners.Append(mpi_test_printer.get());
}

void gtest_mpi::finalize() {
    auto &listeners = testing::UnitTest::GetInstance()->listeners();

    if (!mpi_test_printer) {
        std::cerr << "gtest_mpi::finalize was called without a matching call to gtest_mpi::init!"
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }

    listeners.Release(mpi_test_printer.get());

    mpi_test_printer.reset();
}