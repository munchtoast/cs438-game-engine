cmake_minimum_required(VERSION 3.25)

project(game-engine)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GOOGLETEST_VERSION 1.10.0)

# Include submodules
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/SDL)
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/googletest/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/mimalloc)
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/spdlog)

# Add source files
set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/window.cpp)
set(HEADERS ${CMAKE_SOURCE_DIR}/src/window.h)

add_executable(game-engine ${SOURCES} ${HEADERS})

target_link_libraries(game-engine PRIVATE SDL3::SDL3 mimalloc)
target_link_libraries(game-engine PRIVATE spdlog)

target_include_directories(game-engine PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# ---- Add Testing Support ----
enable_testing()

# Include the tests directory
add_subdirectory(test)
