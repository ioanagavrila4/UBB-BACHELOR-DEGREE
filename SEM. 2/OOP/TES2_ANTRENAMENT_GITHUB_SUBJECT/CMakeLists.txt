cmake_minimum_required(VERSION 3.30)
project(TES2_ANTRENAMENT_GITHUB_SUBJECT)

set(CMAKE_CXX_STANDARD 20)

add_executable(TES2_ANTRENAMENT_GITHUB_SUBJECT main.cpp
        Controller/controller.cpp
        Domain/domain.cpp
        UI/ui.cpp)
