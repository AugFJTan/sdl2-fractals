cmake_minimum_required(VERSION 3.5.0)

project(SDL2_Fractals VERSION 0.1.0 LANGUAGES C CXX)

add_executable(main
               src/main.cpp
               src/utils.cpp
               src/sierpinski_triangle.cpp
               src/sierpinski_carpet.cpp
               src/fractal_tree.cpp
               src/koch_snowflake.cpp
               src/mandelbrot_set.cpp)

set_target_properties(main PROPERTIES LINK_FLAGS "-L${SDL2_LIB}")

target_include_directories(main PUBLIC "${SDL2_INCLUDE}" PRIVATE include)

target_link_libraries(main mingw32 SDL2main SDL2)
