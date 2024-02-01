# test/CMakeLists.txt

# Add a target for the test runner
add_executable(test_tile Test_Tile.cpp)

# Link against the library and testing framework
target_link_libraries(test_tile PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(test_tile PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "Test_Tile.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/Tile.cpp
  ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
)

target_sources(test_tile PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_tile PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME TileTest COMMAND test_tile)
