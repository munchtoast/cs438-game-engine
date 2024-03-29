cmake_minimum_required(VERSION 3.25)

project(game-engine)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GOOGLETEST_VERSION 1.10.0)

# Toggle options for build testing
option(BUILD_TESTING "Build the testing tree" OFF)

# Include submodules
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/SDL)
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/googletest/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/mimalloc)
add_subdirectory(${CMAKE_SOURCE_DIR}/submodule/spdlog)

# Add source files, include *.cpp and *.h
set(SOURCES 
  ${CMAKE_SOURCE_DIR}/src/Util.cpp
  ${CMAKE_SOURCE_DIR}/src/Main.cpp 
  ${CMAKE_SOURCE_DIR}/src/GameWindow.cpp 
  ${CMAKE_SOURCE_DIR}/src/GameObject.cpp 
  ${CMAKE_SOURCE_DIR}/src/Tile.cpp
  ${CMAKE_SOURCE_DIR}/src/UI.cpp
  ${CMAKE_SOURCE_DIR}/src/Controller.cpp
  ${CMAKE_SOURCE_DIR}/src/Animation.cpp
)

include_directories(include)

add_executable(game-engine ${SOURCES})

target_link_libraries(game-engine PRIVATE SDL3::SDL3 mimalloc)
target_link_libraries(game-engine PRIVATE spdlog)

target_include_directories(game-engine PRIVATE ${CMAKE_SOURCE_DIR}/submodule/cute_headers)

# ---- Add Testing Support ----
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test/GameObject_Test)
  add_subdirectory(test/GameWindow_Test)
  add_subdirectory(test/Tile_Test)
  add_subdirectory(test/Util_Test)
  add_subdirectory(test/MemoryManagement_Test)
  add_subdirectory(test/Map_Test)
  add_subdirectory(test/UI_Test)
  add_subdirectory(test/Handler_Test)
  add_subdirectory(test/EventHandler_Test)
  add_subdirectory(test/Controller_Test)
  add_subdirectory(test/Animation_Test)
endif()
