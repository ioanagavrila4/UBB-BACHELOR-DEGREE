cmake_minimum_required(VERSION 3.30)
project(ANTRENAMENT_TEST_4_BILLS)

set(CMAKE_CXX_STANDARD 20)

add_executable(ANTRENAMENT_TEST_4_BILLS
        main.cpp
        Domain/Bill.h
        Domain/Bill.cpp
        Repository/Repo.h
        Repository/Repo.cpp
        Service/Service.cpp
        Service/Service.h
        UI/Ui.cpp
        UI/Ui.h
)
