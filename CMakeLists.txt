cmake_minimum_required(VERSION 3.17)
project(Inverse_Kinematics)

include_directories("D:/opencv-3.1.0/opencv/build/include")
link_directories("D:/opencv-3.1.0/opencv/build/x64/vc12/lib")
link_libraries(opencv_world310d.lib)


set(CMAKE_CXX_STANDARD 11)

add_executable(Inverse_Kinematics main.cpp Arm.cpp)