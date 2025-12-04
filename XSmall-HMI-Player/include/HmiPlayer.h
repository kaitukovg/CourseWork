#ifndef HMIPLAYER_H
#define HMIPLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "VariableDatabase.h"  
#include "VisualObject.h"     

/**
 * Управляющий класс приложения. Реализует главный цикл (game loop):
 * 1. Обработка событий
 * 2. Обновление состояния
 * 3. Отрисовка
 */
class HmiPlayer {
private:
    sf::RenderWindow window;   // Главное окно
    VariableDatabase database; // База данных переменных
    std::vector<std::unique_ptr<VisualObject>> objects;  // Все визуальные объекты
    sf::Font font;  // Основной шрифт
    
public:
    HmiPlayer();

    // Инициализация: загрузка шрифтов, создание объектов
    bool initialize();

    // Главный цикл приложения
    void run();

    // Методы главного цикла
    void handleEvents();
    void update();
    void render();
};

#endif