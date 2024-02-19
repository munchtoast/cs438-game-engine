# test/CMakeLists.txt

include_directories(include)

# Add a target for the test runner
add_executable(test_memoryManagement Test_MemoryManagement.cpp)

# Link against the library and testing framework
target_link_libraries(test_memoryManagement PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(test_memoryManagement PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "Test_MemoryManagement.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
)

target_sources(test_memoryManagement PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_memoryManagement PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME MemoryManagementTest COMMAND test_memoryManagement)
