# test/CMakeLists.txt

include_directories(include)

# Add a target for the test runner
add_executable(test_animation Test_Animation.cpp)
add_executable(test_cel Test_Cel.cpp)

# Link against the library and testing framework
target_link_libraries(test_animation PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)
target_link_libraries(test_cel PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(test_animation PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)
target_include_directories(test_cel PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_ANIMATION_SOURCES "Test_Animation.cpp")
set(TEST_CEL_SOURCES "Test_Cel.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
  ${CMAKE_SOURCE_DIR}/src/Animation.cpp
)

target_sources(test_animation PRIVATE ${TEST_ANIMATION_SOURCES} ${SOURCE_TARGET})
target_sources(test_cel PRIVATE ${TEST_CEL_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_animation PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
set_property(TARGET test_cel PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME AnimationTest COMMAND test_animation)
add_test(NAME CelTest COMMAND test_cel)
