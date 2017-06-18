cmake_minimum_required(VERSION 3.7)

project(edsl.gen LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS On)

find_package(Boost 1.63 REQUIRED)

add_compile_options(-std=c++1z)
add_compile_options(-stdlib=libc++)
set(CMAKE_EXE_LINKER_FLAGS -stdlib=libc++)

include_directories(${Boost_INCLUDE_DIRS})


add_library(edsl.gen INTERFACE)
target_include_directories(edsl.gen INTERFACE include)

include_directories(${edsl.gen_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(example)
add_subdirectory(test)
