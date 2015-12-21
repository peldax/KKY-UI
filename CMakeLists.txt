cmake_minimum_required(VERSION 3.3)
project(UI_semestral_work)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp Node.hpp ClosedList.hpp Core.hpp Executor.hpp Executor.cpp OpenList.hpp)
add_executable(UI_semestral_work ${SOURCE_FILES})