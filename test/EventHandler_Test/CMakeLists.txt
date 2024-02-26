# test/CMakeLists.txt

include_directories(include)

# Add a target for the test runner
add_executable(test_eventHandler Test_EventHandler.cpp)

# Link against the library and testing framework
target_link_libraries(test_eventHandler PRIVATE SDL3::SDL3 gtest gtest_main mimalloc spdlog)

target_include_directories(test_eventHandler PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# Add test source files
set(TEST_SOURCES "Test_EventHandler.cpp")

# Add source targets
set(SOURCE_TARGET 
  ${CMAKE_SOURCE_DIR}/src/GameObject.cpp
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
  ${CMAKE_SOURCE_DIR}/src/Animation.cpp
)

target_sources(test_eventHandler PRIVATE ${TEST_SOURCES} ${SOURCE_TARGET})

# Set the working directory for the test runner
set_property(TARGET test_eventHandler PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

# Add test
add_test(NAME EventHandlerTest COMMAND test_eventHandler)
