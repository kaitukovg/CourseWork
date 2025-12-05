# XSmall-HMI SCADA Player

Проигрыватель SCADA-экранов с поддержкой визуальных объектов и базой переменных.

## 📋 Содержание
- [Особенности](#особенности)
- [Структура проекта](#структура)
- [Требования](#требования)
- [Сборка](#сборка)
- [Тесты](#тесты)

## Особенности

### Основные возможности
- **Визуальные объекты**: Прямоугольники, текст, линии, ломаные линии, поля ввода, кнопки, графики истории, изображения
- **Связь с переменными**: Автоматическое обновление объектов при изменении значений в базе данных
- **Динамическое обновление**: Графики обновляются в реальном времени
- **Сохранение состояния**: Автоматическое сохранение и загрузка состояния системы
- **Модульные тесты**: Полное покрытие тестами с использованием Google Test

### Технические особенности
- **C++17**: Использование современных возможностей языка
- **Статическая сборка**: Один исполняемый файл без зависимостей DLL
- **Автоматическая загрузка зависимостей**: SFML и Google Test загружаются автоматически через CMake FetchContent
- **Кроссплатформенность**: Работает на Windows и Linux

## Структура проекта

├── CMakeLists.txt

├── LICENSE

├── README.md

├── include/

│   ├── VariableDatabase.h

│   ├── VisualObject.h

│   ├── Rectangle.h

│   ├── Text.h

│   ├── Line.h

│   ├── Polyline.h

│   ├── InputField.h

│   ├── Button.h

│   ├── HistoryGraph.h

│   ├── Image.h

│   ├── SceneFactory.h

│   ├── resources.h

│   ├── logger.h

│   ├── Constants.h

│   └── HmiPlayer.h

├── src/

│   ├── main.cpp

│   ├── VariableDatabase.cpp

│   ├── VisualObject.cpp

│   ├── Rectangle.cpp

│   ├── Text.cpp

│   ├── Line.cpp

│   ├── Polyline.cpp

│   ├── InputField.cpp

│   ├── Button.cpp

│   ├── HistoryGraph.cpp

│   ├── Image.cpp

│   ├── SceneFactory.cpp

│   ├── logger.cpp

│   └── HmiPlayer.cpp

├── tests/

│   ├── CMakeLists.txt

│   ├── test_main.cpp

│   ├── test_variable_database.cpp

│   ├── test_scene_factory.cpp

│   └── test_visual_objects.cpp                

├── saved_state.json

└── assets/

    ├── fonts/
    
    │   └── helveticabold.ttf
    
    └── images/
    
        └── logo.png


## Требования

### Минимальные требования
- **ОС**: Windows 10/11 или Linux
- **Компилятор**: GCC 10+ или MinGW-w64
- **CMake**: версия 3.15+
- **Память**: 2 ГБ ОЗУ
- **Дисковое пространство**: 500 МБ

### Зависимости (загружаются автоматически)
- **SFML 2.6.1**: Графическая библиотека
- **Google Test 1.14.0**: Фреймворк для модульного тестирования

## Сборка

### Windows (Git Bash / MinGW)
```bash
# Клонирование репозитория
git clone https://github.com/kaitukovg/CourseWork.git
cd XSmall-HMI-Player

# Сборка проекта
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build . -- -j4

# Запуск программы
./HMI_Player.exe
```

#### Тесты
```bash
cd tests
./HMI_Tests.exe
```
