#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "VisualObject.h"
#include "VariableDatabase.h"
#include <SFML/Graphics.hpp>

/**
 * Прямоугольный элемент, меняющий цвет в зависимости от значения переменной.
 * Используется для индикации состояния (норма/предупреждение/авария).
 */
class Rectangle : public VisualObject {
private:
    float width, height;
    sf::RectangleShape shape;
    sf::Color defaultColor;   // Цвет по умолчанию
    std::string variableName; // Имя связанной переменной
    
    // Условия изменения цвета: значение -> цвет
    struct ColorCondition {
        double value;
        sf::Color color;
    };
    std::vector<ColorCondition> conditions;

public:
    Rectangle(float x, float y, float width, float height, 
              const sf::Color& color, const std::string& name,
              VariableDatabase* db, const std::string& varName = "");
    
    void draw(sf::RenderWindow& window) override;
    void update() override;

    // Добавляет условие: при значении `value` прямоугольник окрашивается в `color`
    void addCondition(double value, const sf::Color& color);
};

#endif