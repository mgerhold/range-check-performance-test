include(${PROJECT_SOURCE_DIR}/cmake/warnings.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/sanitizers.cmake)

# the following function was taken from:
# https://github.com/cpp-best-practices/cmake_template/blob/main/ProjectOptions.cmake
macro(check_sanitizer_support)
    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
        set(supports_ubsan ON)
    else ()
        set(supports_ubsan OFF)
    endif ()

    if ((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
        set(supports_asan OFF)
    else ()
        set(supports_asan ON)
    endif ()
endmacro()

if (PROJECT_IS_TOP_LEVEL)
    option(range_check_performance_test_warnings_as_errors "Treat warnings as errors" ON)
    option(range_check_performance_test_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" ${supports_ubsan})
    option(range_check_performance_test_enable_address_sanitizer "Enable address sanitizer" ${supports_asan})
    option(obpf_build_tests "Build unit tests" ON)
else ()
    option(range_check_performance_test_warnings_as_errors "Treat warnings as errors" OFF)
    option(range_check_performance_test_enable_undefined_behavior_sanitizer "Enable undefined behavior sanitizer" OFF)
    option(range_check_performance_test_enable_address_sanitizer "Enable address sanitizer" OFF)
    option(obpf_build_tests "Build unit tests" OFF)
endif ()
option(range_check_performance_test_build_shared_libs "Build shared libraries instead of static libraries" ON)
set(BUILD_SHARED_LIBS ${range_check_performance_test_build_shared_libs})

add_library(range_check_performance_test_warnings INTERFACE)
range_check_performance_test_set_warnings(range_check_performance_test_warnings ${range_check_performance_test_warnings_as_errors})

add_library(range_check_performance_test_sanitizers INTERFACE)
range_check_performance_test_enable_sanitizers(range_check_performance_test_sanitizers ${range_check_performance_test_enable_address_sanitizer} ${range_check_performance_test_enable_undefined_behavior_sanitizer})

add_library(range_check_performance_test_project_options INTERFACE)
target_link_libraries(range_check_performance_test_project_options
        INTERFACE range_check_performance_test_warnings
        INTERFACE range_check_performance_test_sanitizers
)
