cmake_minimum_required(VERSION 3.20.0)
project(jacll VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#include all header files in inc directory 
include_directories(inc "inc/")

#link and include header files for llvm
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(jacll 
    src/main.cpp
    src/Token.cpp    
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(jacll ${llvm_libs})


####BEGIN gtest content

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(
  TokenTest
  src/Token.cpp
  test/Token/Token.test.cpp
)
target_link_libraries(
  TokenTest
  GTest::gtest_main
)

add_test(TokenTest TokenTest)

include(GoogleTest)

gtest_discover_tests(TokenTest)