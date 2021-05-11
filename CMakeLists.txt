cmake_minimum_required(VERSION 3.19)
project(Vector_Space)

set(CMAKE_CXX_STANDARD 14)

add_executable(Vector_Space main.cpp Vector.h Matrix.h VectorSpaceException.h VectorSpace.h LinearMap.h)