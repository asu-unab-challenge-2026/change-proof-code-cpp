cmake_minimum_required(VERSION 3.16)
project(ChangeProofCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4 /utf-8)
else()
  add_compile_options(-Wall -Wextra)
endif()

# Every .cpp you add to src/ or tests/ is picked up automatically.
file(GLOB CAMPUS_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/tests/*.cpp)

add_library(campus STATIC ${CAMPUS_SOURCES})
target_include_directories(campus PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(campus_demo app/main.cpp)
target_link_libraries(campus_demo PRIVATE campus)

add_executable(run_tests ${TEST_SOURCES})
target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/tests)
target_link_libraries(run_tests PRIVATE campus)

enable_testing()
add_test(NAME all_tests COMMAND run_tests)
