# test/CMakeLists.txt

include_directories(include)

# Add a target for the test runner
add_executable(test_collision Test_Collision.cpp)

# Link against the library and testing framework
target_link_libraries(test_collision PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(test_collision PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "Test_Collision.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
  ${CMAKE_SOURCE_DIR}/src/BoxRigidBody.cpp
  ${CMAKE_SOURCE_DIR}/src/Animation.cpp
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
  ${CMAKE_SOURCE_DIR}/src/Collision.cpp
)

target_sources(test_collision PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_collision PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME CollisionTest COMMAND test_collision)
