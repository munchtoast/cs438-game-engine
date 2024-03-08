# CMake generated Testfile for 
# Source directory: D:/CS438/game-engine/submodule/mimalloc
# Build directory: D:/CS438/game-engine/out/build/x64-Debug/submodule/mimalloc
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test-api "D:/CS438/game-engine/out/build/x64-Debug/submodule/mimalloc/mimalloc-test-api.exe")
set_tests_properties(test-api PROPERTIES  _BACKTRACE_TRIPLES "D:/CS438/game-engine/submodule/mimalloc/CMakeLists.txt;506;add_test;D:/CS438/game-engine/submodule/mimalloc/CMakeLists.txt;0;")
add_test(test-api-fill "D:/CS438/game-engine/out/build/x64-Debug/submodule/mimalloc/mimalloc-test-api-fill.exe")
set_tests_properties(test-api-fill PROPERTIES  _BACKTRACE_TRIPLES "D:/CS438/game-engine/submodule/mimalloc/CMakeLists.txt;506;add_test;D:/CS438/game-engine/submodule/mimalloc/CMakeLists.txt;0;")
add_test(test-stress "D:/CS438/game-engine/out/build/x64-Debug/submodule/mimalloc/mimalloc-test-stress.exe")
set_tests_properties(test-stress PROPERTIES  _BACKTRACE_TRIPLES "D:/CS438/game-engine/submodule/mimalloc/CMakeLists.txt;506;add_test;D:/CS438/game-engine/submodule/mimalloc/CMakeLists.txt;0;")
