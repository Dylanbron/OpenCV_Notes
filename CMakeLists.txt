cmake_minimum_required(VERSION 3.10)
project(Test)

#CMake通过此命令自动寻找OpenCV的依赖
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
include_directories(/usr/local/include/opencv4)

add_executable(Test main3.cpp)
target_link_libraries(Test ${OpenCV_LIBRARIES})
