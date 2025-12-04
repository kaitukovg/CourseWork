#include "Rectangle.h"
#include "logger.h"

Rectangle::Rectangle(float x, float y, float width, float height, 
                     const sf::Color& color, const std::string& name,
                     VariableDatabase* db, const std::string& varName)
    : VisualObject(x, y, name, db), width(width), height(height), 
      defaultColor(color), variableName(varName) {
    
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    
    // Подписываемся на изменения переменной для автоматического обновления цвета
    if (!variableName.empty() && database) {
        database->subscribe(variableName, [this](double value) {
            this->update();
        });
    }
}

void Rectangle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Rectangle::update() {
    if (!variableName.empty() && database) {
        double value = database->getVariable(variableName);
        sf::Color newColor = defaultColor;
        
        // Проверяем все условия для изменения цвета
        for (const auto& condition : conditions) {
            if (value == condition.value) {
                newColor = condition.color;
                break;  // Первое подходящее условие
            }
        }
        
        shape.setFillColor(newColor);
    }
}

void Rectangle::addCondition(double value, const sf::Color& color) {
    conditions.push_back({value, color});
}