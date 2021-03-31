cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)

get_filename_component(PROJECT ${CMAKE_SOURCE_DIR} NAME)
project(${PROJECT})

find_package(OpenCV REQUIRED)

file(GLOB C_SOURCES *.c)
file(GLOB CPP_SOURCES *.cpp)

set(SOURCES ${C_SOURCES} ${CPP_SOURCES}
        app/main.cpp

        include/_webots/Controller.hpp
        include/_webots/Wheel.hpp
        include/_webots/Encoder.hpp
        include/Robot.hpp
        include/ImageProc.hpp
        include/_webots/MotorizedCamera.hpp

        src/_webots/Controller.cpp
        src/_webots/Wheel.cpp
        src/_webots/Encoder.cpp
        src/Robot.cpp
        src/ImageProc.cpp
        src/_webots/MotorizedCamera.cpp

        tests/camera_test.cpp
        tests/hsv_test.cpp include/Numbers.hpp)

link_directories(/usr/local/webots/lib/controller)
set(LIBRARIES /usr/local/webots/lib/controller/libController.so Controller${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CppController${CMAKE_SHARED_LIBRARY_SUFFIX} ${OpenCV_LIBS})
include_directories(/usr/local/webots/lib/controller /usr/local/webots/include/controller/c /usr/local/webots/include/controller/cpp ${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${LIBRARIES})

add_custom_command(TARGET ${PROJECT} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${PROJECT} ${CMAKE_SOURCE_DIR}/bin)