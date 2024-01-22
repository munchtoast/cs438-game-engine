cmake_minimum_required(VERSION 3.25)

project(game-engine)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GOOGLETEST_VERSION 1.10.0)

# Include submodules
add_subdirectory(submodule/SDL)
add_subdirectory(submodule/googletest/googletest)
add_subdirectory(submodule/mimalloc)
add_subdirectory(submodule/spdlog)

# Add your source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create a library from the common source files
add_library(GameEngineLib ${SOURCES})

# Specify include directories for the library
target_include_directories(GameEngineLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/SDL/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/mimalloc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/submodule/cute_headers  # Include the header-only library
)

# Create the main executable using the library
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE GameEngineLib)

# ---- Add Testing Support ----
enable_testing()

# Include the tests directory
add_subdirectory(test)
