cmake_minimum_required(VERSION 3.30)
project(TEST2_ANTRENAMENT_OLD_BUILDINGS)

set(CMAKE_CXX_STANDARD 20)

add_executable(TEST2_ANTRENAMENT_OLD_BUILDINGS main.cpp
        Controller/Controller.cpp
        Domain/Domain.cpp
        UI/ui.cpp
        Controller/Controller.h
        Domain/Domain.h
        UI/ui.h

)
