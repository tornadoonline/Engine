cmake_minimum_required(VERSION 3.7)

project(Engine LANGUAGES CXX
)
set(Engine_SOVERSION 3)
set(Engine_RELEASE_CANDIDATE 0)
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)

set(CMAKE_CXX_FLAGS_DEBUG "/MD")

set(Engine_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "Root source directory of Engine")
set(Engine_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE INTERNAL "Root binary directory of Engine")

# set the use of C++17 globally as all examples require it
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QT_PACKAGE_NAME Qt5 CACHE STRING "Set Qt package name, i.e. Qt5 or Qt6.")

set(Qt5_DIR "C:/Qt/Qt5.14.2/5.14.2/msvc2017_64")
set(VSG_DIR "D:/Work/Build/vsg")
set(VSGXChange_DIR "D:/Work/Build/vsgXchange")
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})
list(APPEND CMAKE_PREFIX_PATH ${VSG_DIR})
list(APPEND CMAKE_PREFIX_PATH ${VSGXChange_DIR})

find_package(vsg 1.1.2)
find_package(vsgXchange)

find_package(${QT_PACKAGE_NAME} COMPONENTS Widgets REQUIRED)

file(GLOB Engine_cpp_SRC src/*.cpp)
file(GLOB Engine_hpp_SRC src/*.h)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
    add_definitions(-DNOMINMAX)
    set(MODE WIN32)
endif()

add_subdirectory(src)

add_executable(QtMdi main.cpp)

target_link_libraries(QtMdi Engine::Engine vsgXchange::vsgXchange)