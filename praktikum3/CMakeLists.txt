cmake_minimum_required(VERSION 3.10)
project(praktikum3)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} 
  main.cc
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
