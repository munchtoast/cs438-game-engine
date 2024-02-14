# test/CMakeLists.txt

include_directories(include)

# Add a target for the test runner
add_executable(test_gameWindow Test_GameWindow.cpp)

# Link against the library and testing framework
target_link_libraries(test_gameWindow PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(test_gameWindow PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "Test_GameWindow.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/GameWindow.cpp
  ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
)

target_sources(test_gameWindow PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_gameWindow PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME GameWindowTest COMMAND test_gameWindow)
