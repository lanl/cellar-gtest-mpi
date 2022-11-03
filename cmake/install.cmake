include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/gtest-mpiConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/gtest-mpiConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/gtest-mpiConfig.cmake"
    INSTALL_DESTINATION lib/cmake/gtest-mpi
)

install(FILES
    "${PROJECT_BINARY_DIR}/gtest-mpiConfigVersion.cmake"
    "${PROJECT_BINARY_DIR}/gtest-mpiConfig.cmake"
    DESTINATION lib/cmake/gtest-mpi
    )