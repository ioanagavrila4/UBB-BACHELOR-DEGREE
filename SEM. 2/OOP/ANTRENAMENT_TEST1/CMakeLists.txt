cmake_minimum_required(VERSION 3.30)
project(ANTRENAMENT_TEST1)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        ANTRENAMENT_TEST1
        main.cpp
        Domain/School.h
        Domain/School.cpp
        Repo/Repository.h
        Repo/Repository.cpp
        Service/Service.h
        Service/Service.cpp
        UI/ui.h
        UI/ui.cpp

)
