cmake_minimum_required(VERSION 3.14)
project(PNG-image-of-the-IEC-61499-function-block)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

# Скачиваем и собираем pugixml
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.14
    GIT_SHALLOW TRUE
)

# Скачиваем и собираем SFML
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW TRUE
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(pugixml sfml)

add_executable(main src/main.cpp src/Parser.cpp src/FB_lib_graphic.cpp src/FB_Visualizer.cpp)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${pugixml_SOURCE_DIR}/src
    ${sfml_SOURCE_DIR}/include
)

target_link_libraries(main PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    pugixml-static
)