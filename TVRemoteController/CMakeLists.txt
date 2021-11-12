cmake_minimum_required(VERSION 3.19)
project(TVRemoteController)

set(CMAKE_CXX_STANDARD 20 CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework GLUT -framework OpenGL") # compiler version and compiler flags.

add_executable(TVRemoteController Main.cpp Circle3D.h Cilinder3D.h Object3D.h ScreenHelper.h ScreenHelper.cpp Window.h WorldState.h Primitive3D.h Point3D.h Math.h Observer.h OpenGL.h Vector3D.h ../../../../cygwin64/usr/include/w32api/GL/glut.h)