# test/CMakeLists.txt

# Add a target for the test runner
add_executable(test_runner test_main.cpp)

# Link against the library and testing framework
target_link_libraries(test_runner PRIVATE GameEngineLib gtest)

# Add your test source files
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
target_sources(test_runner PRIVATE ${TEST_SOURCES})

# Set the working directory for the test runner
set_property(TARGET test_runner PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add a test
add_test(NAME MyTest COMMAND test_runner)
