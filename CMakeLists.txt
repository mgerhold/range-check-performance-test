cmake_minimum_required(VERSION 3.25)
project(range_check_performance_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(dependencies.cmake)
range_check_performance_test_setup_dependencies()

include(project_options.cmake)

add_subdirectory(src bin)
