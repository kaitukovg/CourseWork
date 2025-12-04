#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

/**
 * Централизованное хранение констант проекта.
 * Упрощает изменение настроек и поддержку кода.
 */
namespace Constants {
    const int WINDOW_WIDTH = 1024;  // Ширина основное окна 
    const int WINDOW_HEIGHT = 768;  // Высота основного окна
    const std::string FONT_PATH = "assets/fonts/helveticabold.ttf";  // Основной шрифт
    //const std::string CONFIG_PATH = "config/default_screen.xml";  // Кон
}

#endif