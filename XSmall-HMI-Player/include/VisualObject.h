#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <VariableDatabase.h>

class VariableDatabase;

/** Базовый класс для всех графический элементов 
 * Определяет интерфейс для отрисовки, обновления и обработки событий
*/

class VisualObject {
protected:
    float x, y;                  // Позиция на экране
    std::string name;            // Уникальное имя объекта
    VariableDatabase* database;  // Ссылка на базу данных для синхронизации

public:
    VisualObject(float x, float y, const std::string& name, VariableDatabase* db);
    virtual ~VisualObject() = default;
    
    // Чисто виртуальные методы (должны быть реализованы в наследниках)
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update() = 0;

    // Виртуальный метод с реализацией по умолчанию
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) {};
    
    // Вспомогательные методы
    void setPosition(float newX, float newY);
    std::string getName() const;
};

#endif