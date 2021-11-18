cmake_minimum_required(VERSION 3.19)
project(TVRemoteController)

set(CMAKE_CXX_STANDARD 20) # compiler version and compiler flags.
add_executable(TVRemoteController Main.cpp Circle3D.h Cilinder3D.h Object3D.h ScreenHelper.h GLWindow.h WorldState.h Primitive3D.h Point3D.h Math.h Observer.h OpenGL.h Vector3D.h ObserverEnum.h)
target_link_libraries(TVRemoteController -lglut -lGL -lGLU -lX11)
