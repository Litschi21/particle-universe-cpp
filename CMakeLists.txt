cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME particle_universe)
project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)
add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wshadow -Wnull-dereference -Wformat=2 -Werror)
target_link_libraries(${PROJECT_NAME}
  PRIVATE SFML::Graphics
)
