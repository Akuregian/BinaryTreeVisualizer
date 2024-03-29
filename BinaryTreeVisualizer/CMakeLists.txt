﻿# CMakeList.txt : CMake project for BinaryTreeVisualizer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

file(GLOB_RECURSE HEADERS "Headers/*.hpp" "../Utility/*.hpp")
file(GLOB_RECURSE SRC "Source/*.cpp" )

# Add source to this project's executable.
add_executable (BinaryTreeVisualizer ${HEADERS} ${SRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BinaryTreeVisualizer PROPERTY CXX_STANDARD 20)
endif()

find_package(glad CONFIG REQUIRED)
target_link_libraries(BinaryTreeVisualizer PRIVATE glad::glad)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(BinaryTreeVisualizer PRIVATE imgui::imgui)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(BinaryTreeVisualizer PRIVATE glfw)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(BinaryTreeVisualizer PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

find_package(ImGui-SFML CONFIG REQUIRED)
target_link_libraries(BinaryTreeVisualizer PRIVATE ImGui-SFML::ImGui-SFML)

