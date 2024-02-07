# test/CMakeLists.txt

# Add a target for the test runner
add_executable(test_camera Test_UI.cpp)

# Link against the library and testing framework
target_link_libraries(test_camera PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(test_camera PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "Test_UI.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/UI.cpp
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
  ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
  ${CMAKE_SOURCE_DIR}/src/MemoryManagement.cpp
)

target_sources(test_camera PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_camera PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME UITest COMMAND test_camera)
