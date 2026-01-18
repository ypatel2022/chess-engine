cmake_minimum_required(VERSION 3.28)
project(chess_engine LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 3.0.2
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
FetchContent_MakeAvailable(SFML)

# Define executable
add_executable(
    ${PROJECT_NAME}

    src/main.cpp
    src/board.cpp

    include/board.h
    include/utils.h
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
