cmake_minimum_required(VERSION 3.26)
project(snake)

set(CMAKE_CXX_STANDARD 20)
set(RAYLIB_VERSION 5.0)

find_package(raylib ${RAYLIB_VERSION} REQUIRED)

add_executable(snake main.cpp
)

target_link_libraries(snake raylib)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()