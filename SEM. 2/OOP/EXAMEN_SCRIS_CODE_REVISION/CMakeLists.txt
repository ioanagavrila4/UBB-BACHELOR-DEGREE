cmake_minimum_required(VERSION 3.30)
project(EXAMEN_SCRIS_CODE_REVISION)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/ioanagavrila/Qt/6.9.0/macos")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

add_executable(EXAMEN_SCRIS_CODE_REVISION main.cpp
        Domain/domain.cpp
        UI/ui.cpp
        Service/service.cpp
        UI/ui.cpp)

target_link_libraries(EXAMEN_SCRIS_CODE_REVISION
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)