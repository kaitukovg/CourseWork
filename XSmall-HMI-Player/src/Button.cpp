#include "Button.h"
#include "logger.h"

Button::Button(float x, float y, float width, float height,
               const std::string& buttonText, sf::Font* font, unsigned int fontSize,
               const sf::Color& color, const std::string& name, VariableDatabase* db,
               const std::string& varName, std::function<void()> onClickFunc,
               const sf::Color& textClr)  
    : VisualObject(x, y, name, db), font(font), variableName(varName),
      normalColor(color), 
      // Автоматически генерируем цвета для состояний hover и pressed
      hoverColor(sf::Color(std::max(0, color.r - 30), std::max(0, color.g - 30), std::max(0, color.b - 30), color.a)),
      pressedColor(sf::Color(std::max(0, color.r - 50), std::max(0, color.g - 50), std::max(0, color.b - 50), color.a)),
      textColor(textClr),
      isHovered(false), isPressed(false), onClick(onClickFunc) {
    
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(normalColor);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
    
    // Центрируем текст внутри кнопки
    text.setPosition(x + width / 2, y + height / 2);
    text.setFont(*font);
    text.setString(buttonText);
    text.setCharacterSize(fontSize);
    text.setFillColor(textColor); 
    
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2, 
                   textBounds.top + textBounds.height / 2);
    
    if (!variableName.empty() && database) {
        database->subscribe(variableName, [this](double value) {
            this->update();
        });
    }
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

void Button::update() {
    if (!variableName.empty() && database) {
        // Кнопка, привязанная к переменной: цвет зависит от значения
        double value = database->getVariable(variableName);
        if (value == 0) {
            shape.setFillColor(normalColor);
        } else {
            shape.setFillColor(pressedColor);
        }
    } else {
        // Обычная кнопка: цвет зависит от состояние мыши
        if (isPressed) {
            shape.setFillColor(pressedColor);
        } else if (isHovered) {
            shape.setFillColor(hoverColor);
        } else {
            shape.setFillColor(normalColor);
        }
    }
}

void Button::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool mouseOver = contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    
    if (event.type == sf::Event::MouseMoved) {
        isHovered = mouseOver;
        update();
    }
    
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && mouseOver) {
            isPressed = true;
            update();
        }
    }
    
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left && isPressed && mouseOver) {
            if (onClick) {
                onClick();
            }
            isPressed = false;
            update();
        }
    }
}

// Проверяем находится ли точка внутри кнопки 
bool Button::contains(float pointX, float pointY) const {
    return pointX >= x && pointX <= x + shape.getSize().x &&
           pointY >= y && pointY <= y + shape.getSize().y;
}

void Button::setOnClick(std::function<void()> onClickFunc) {
    onClick = onClickFunc;
}

void Button::setTextColor(const sf::Color& color) {
    textColor = color;
    text.setFillColor(textColor);
}