# test/CMakeLists.txt

# Add a target for the test runner
add_executable(test_runner test_main.cpp)

# Link against the library and testing framework
target_link_libraries(test_runner PRIVATE SDL3::SDL3 gtest mimalloc spdlog)

target_include_directories(test_runner PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "test_main.cpp")

# Add source targets
set(SOURCE_TARGET ${CMAKE_SOURCE_DIR}/src/window.cpp)

target_sources(test_runner PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_runner PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME MyTest COMMAND test_runner)
