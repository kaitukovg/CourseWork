cmake_minimum_required(VERSION 3.15)
project(HMI_Tests)

# ЯВНО УСТАНАВЛИВАЕМ С++17 ДЛЯ ТЕСТОВ!
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "=== Настройка модульных тестов (отдельная сборка) ===")

# Настраиваем пути
set(SFML_PATH "C:/Libraries/SFML")
set(GTEST_ROOT "C:/Libraries/gtest")

message(STATUS "Ищем SFML в: ${SFML_PATH}")
message(STATUS "Ищем GTest в: ${GTEST_ROOT}")

# Проверяем SFML
if(NOT EXISTS "${SFML_PATH}/include/SFML/Graphics.hpp")
    message(FATAL_ERROR "❌ SFML не найден в: ${SFML_PATH}")
endif()

# Проверяем GTest
if(NOT EXISTS "${GTEST_ROOT}/include/gtest/gtest.h")
    message(FATAL_ERROR "❌ GTest не найден в: ${GTEST_ROOT}")
endif()

# Устанавливаем корневую директорию проекта
get_filename_component(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/.." ABSOLUTE)
message(STATUS "Корень проекта: ${PROJECT_ROOT}")

# Настраиваем пути для заголовков
include_directories(
    ${PROJECT_ROOT}/include
    ${PROJECT_ROOT}/src          # для inline функций, если есть
    ${SFML_PATH}/include
    ${GTEST_ROOT}/include
)

# Определяем библиотеки GTest
if(EXISTS "${GTEST_ROOT}/lib/gtest.lib")
    set(GTEST_LIBRARIES 
        "${GTEST_ROOT}/lib/gtest.lib" 
        "${GTEST_ROOT}/lib/gtest_main.lib"
    )
    message(STATUS "✅ Используем библиотеки .lib")
elseif(EXISTS "${GTEST_ROOT}/lib/libgtest.a")
    set(GTEST_LIBRARIES 
        "${GTEST_ROOT}/lib/libgtest.a" 
        "${GTEST_ROOT}/lib/libgtest_main.a"
    )
    message(STATUS "✅ Используем библиотеки .a")
else()
    message(FATAL_ERROR "❌ Не найдены библиотеки GTest в ${GTEST_ROOT}/lib/")
endif()

# Список тестовых файлов
set(TEST_SOURCES
    test_main.cpp
    test_variable_database.cpp
    test_visual_objects.cpp
    test_xml_loader.cpp
)

# Создаем исполняемый файл для тестов
add_executable(HMI_Tests ${TEST_SOURCES})

# Добавляем ВСЕ исходные файлы проекта, которые нужны для тестов
target_sources(HMI_Tests PRIVATE
    ${PROJECT_ROOT}/src/VariableDatabase.cpp
    ${PROJECT_ROOT}/src/VisualObject.cpp
    ${PROJECT_ROOT}/src/Rectangle.cpp
    ${PROJECT_ROOT}/src/Text.cpp
    ${PROJECT_ROOT}/src/Line.cpp
    ${PROJECT_ROOT}/src/Polyline.cpp
    ${PROJECT_ROOT}/src/InputField.cpp
    ${PROJECT_ROOT}/src/Button.cpp
    ${PROJECT_ROOT}/src/Image.cpp
    ${PROJECT_ROOT}/src/HistoryGraph.cpp
    ${PROJECT_ROOT}/src/SceneFactory.cpp
)

# Подключаем библиотеки
target_link_libraries(HMI_Tests
    ${GTEST_LIBRARIES}
    sfml-graphics
    sfml-window
    sfml-system
)

# Добавляем флаг компилятора для C++17
target_compile_options(HMI_Tests PRIVATE
    -std=c++17
)

# Указываем пути к библиотекам SFML
target_link_directories(HMI_Tests PRIVATE
    ${SFML_PATH}/lib
)

message(STATUS "✅ Тесты настроены успешно! (С++17)")