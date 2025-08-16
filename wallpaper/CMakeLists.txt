cmake_minimum_required(VERSION 3.31)
project(wallpaper)

set(CMAKE_CXX_STANDARD 20)

add_executable(wallpaper main.cpp
        config.h
        CLI11.hpp
)

install(TARGETS wallpaper DESTINATION /usr/local/bin)
