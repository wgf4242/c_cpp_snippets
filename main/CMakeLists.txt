cmake_minimum_required(VERSION 3.19)
project(main)
add_subdirectory("${PROJECT_SOURCE_DIR}/../c_project" "${PROJECT_SOURCE_DIR}/c_project_output")
add_subdirectory("${PROJECT_SOURCE_DIR}/../cpp_project" "${PROJECT_SOURCE_DIR}/cpp_project_output")