cmake_minimum_required(VERSION 3.14)
project(PNG-image-of-the-IEC-61499-function-block)

set(CMAKE_CXX_STANDARD 17)

# Включаем модуль FetchContent
include(FetchContent)

# Скачиваем и собираем SFML из исходников
FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW TRUE
)

# Опционально: отключаем модули, которые не нужны (ускоряет сборку)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)

# Скачиваем и собираем pugixml
# FetchContent_Declare(
#     pugixml
#     GIT_REPOSITORY https://github.com/zeux/pugixml.git
#     GIT_TAG v1.14
#     GIT_SHALLOW TRUE
# )


# Включаем статическую сборку (чтобы не нужны были DLL)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Загружаем SFML
FetchContent_MakeAvailable(sfml)
# FetchContent_MakeAvailable(pugixml)

# Создаем наш исполняемый файл
add_executable(main src/main.cpp src/FB_lib C:\\VSCod\\PNG-image-of-the-IEC-61499-function-block\\pugixml-1.15\\src\\pugixml.cpp)

# Подключаем SFML (используем цели CMake)
target_link_libraries(main PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    # pugixml
)

# Для статической линковки на Windows
if(WIN32)
    # Не нужно SFML_STATIC при использовании FetchContent
    # Автоматически подключаются системные библиотеки
    
    # Для отладки: выводим информацию о библиотеках
    message(STATUS "Using SFML from FetchContent")
    message(STATUS "SFML include dir: ${sfml_SOURCE_DIR}/include")
    # message(STATUS "pugixml include dir: ${pugixml_SOURCE_DIR}/src")
endif()