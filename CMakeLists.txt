cmake_minimum_required(VERSION 3.14)
project(PNG-image-of-the-IEC-61499-function-block)

set(CMAKE_CXX_STANDARD 17)

# Включаем модуль FetchContent
include(FetchContent)

# Скачиваем и собираем pugixml
FetchContent_Declare(
    pugixml
    GIT_REPOSITORY https://github.com/zeux/pugixml.git
    GIT_TAG v1.14
    GIT_SHALLOW TRUE
)

# Скачиваем и собираем SFML из исходников
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW TRUE
)

# Настройки для библиотек
# set(PUGIXML_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
# set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
# set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

# Загружаем библиотеки
FetchContent_MakeAvailable(pugixml sfml)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${pugixml_SOURCE_DIR}/src
    ${sfml_SOURCE_DIR}/include
)

# Создаем исполняемый файл
add_executable(main src/main.cpp src/Parser.cpp src/FB_lib_graphic.cpp src/FB_Visualizer.cpp)

# Подключаем библиотеки
target_link_libraries(main PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    pugixml-static
)

# Добавляем include-директории
target_include_directories(main PRIVATE
    ${pugixml_SOURCE_DIR}/src
)

# Для Windows: флаг для консольного приложения
if(WIN32)
    target_link_options(main PRIVATE -mconsole)
    message(STATUS "Building console application with SFML and pugixml")
endif()