cmake_minimum_required(VERSION 3.15)
project(XSmall-HMI-Player VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========== НАСТРОЙКА SFML ==========
set(SFML_PATH "C:/Libraries/SFML")
message(STATUS "Ищем SFML в: ${SFML_PATH}")

if(NOT EXISTS ${SFML_PATH})
    message(FATAL_ERROR "❌ Путь к SFML не найден: ${SFML_PATH}")
endif()

set(SFML_DIR "${SFML_PATH}/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)
message(STATUS "✅ SFML найден")

# ========== НАСТРОЙКА ПУТЕЙ ==========
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_ROOT}/include ${SFML_INCLUDE_DIR})

# ========== ГЛАВНАЯ ПРОГРАММА ==========
set(SOURCES
    src/main.cpp
    src/VariableDatabase.cpp
    src/VisualObject.cpp
    src/Rectangle.cpp
    src/Text.cpp
    src/Line.cpp
    src/Polyline.cpp
    src/InputField.cpp
    src/Button.cpp
    src/Image.cpp
    src/HistoryGraph.cpp
    src/SceneFactory.cpp
    src/HmiPlayer.cpp
)

add_executable(HMI_Player ${SOURCES})
target_link_libraries(HMI_Player sfml-graphics sfml-window sfml-system)

# Копируем ресурсы
file(COPY ${PROJECT_ROOT}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${PROJECT_ROOT}/config DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "✅ Основное приложение настроено")

# ========== ПОДКЛЮЧАЕМ ТЕСТЫ ==========
add_subdirectory(tests)