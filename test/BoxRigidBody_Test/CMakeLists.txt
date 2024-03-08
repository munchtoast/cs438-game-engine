# test/CMakeLists.txt

include_directories(include)

# Add a target for the test runner
add_executable(Test_boxRigidBody Test_BoxRigidBody.cpp)

# Link against the library and testing framework
target_link_libraries(Test_boxRigidBody PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(Test_boxRigidBody PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "Test_BoxRigidBody.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
  ${CMAKE_SOURCE_DIR}/src/BoxRigidBody.cpp
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
  ${CMAKE_SOURCE_DIR}/src/Animation.cpp
)

target_sources(Test_boxRigidBody PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET Test_boxRigidBody PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME BoxRigidBodyTest COMMAND Test_boxRigidBody)
