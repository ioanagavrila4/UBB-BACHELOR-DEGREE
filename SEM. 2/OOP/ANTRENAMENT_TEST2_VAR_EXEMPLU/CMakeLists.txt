cmake_minimum_required(VERSION 3.30)
project(ANTRENAMENT_TEST2_VAR_EXEMPLU)

set(CMAKE_CXX_STANDARD 20)

add_executable(ANTRENAMENT_TEST2_VAR_EXEMPLU main.cpp
        Domain/Domain.cpp
        Person/Person.cpp
        UI/ui.cpp)
