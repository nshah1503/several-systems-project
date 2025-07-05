cmake_minimum_required(VERSION 3.10)
project(hyperloglog CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable CTest for running tests
enable_testing()

# Create a library for HyperLogLog implementation
add_library(hyperloglog_lib src/hyperloglog.cpp)
target_include_directories(hyperloglog_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Main executable
add_executable(hyperloglog src/main.cpp)
target_include_directories(hyperloglog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(hyperloglog hyperloglog_lib)

# Test executable
add_executable(test_hyperloglog test/test_hyperloglog.cpp)
target_include_directories(test_hyperloglog PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(test_hyperloglog hyperloglog_lib)

# Add test to CTest
add_test(NAME HyperLogLog_Tests COMMAND test_hyperloglog)

# Custom target to run tests after build
add_custom_target(run_tests ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_hyperloglog
    COMMENT "Running HyperLogLog tests..."
)

# Set the main executable as the default target
set_target_properties(hyperloglog PROPERTIES
    OUTPUT_NAME "hyperloglog"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

# Set the test executable output directory
set_target_properties(test_hyperloglog PROPERTIES
    OUTPUT_NAME "test_hyperloglog"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)