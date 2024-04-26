include("${CMAKE_SOURCE_DIR}/cmake/CPM.cmake")
include("${CMAKE_SOURCE_DIR}/cmake/system_link.cmake")

function(range_check_performance_test_setup_dependencies)
    CPMAddPackage(
            NAME GOOGLE_BENCHMARK
            GITHUB_REPOSITORY google/benchmark
            VERSION 1.8.3
            OPTIONS
            "BENCHMARK_ENABLE_INSTALL OFF"
            "BENCHMARK_INSTALL_DOCS OFF"
            "BENCHMARK_BUILD_32_BITS OFF"
            "BENCHMARK_DOWNLOAD_DEPENDENCIES ON"
            "BENCHMARK_ENABLE_GTEST_TESTS OFF"
            "BENCHMARK_ENABLE_ASSEMBLY_TESTS OFF"
    )
    CPMAddPackage(
            NAME LIB2K
            GITHUB_REPOSITORY mgerhold/lib2k
            VERSION 0.0.1
    )
endfunction()
