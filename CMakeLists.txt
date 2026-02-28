cmake_minimum_required(VERSION 3.16)
project(ImageProcessDataFlow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 5.15 REQUIRED COMPONENTS Widgets)

add_executable(ImageProcessDataFlow
    src/main.cpp
    src/ui/mainwindow.h
    src/ui/mainwindow.cpp
    src/ui/nodegraphscene.h
    src/ui/nodegraphscene.cpp
    src/core/processingnode.h
    src/core/noderegistry.h
    src/core/noderegistry.cpp
)

target_link_libraries(ImageProcessDataFlow PRIVATE Qt5::Widgets)
