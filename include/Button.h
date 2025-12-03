#ifndef BUTTON_H
#define BUTTON_H

#include "VisualObject.h"
#include "VariableDatabase.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public VisualObject {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font* font;
    std::string variableName;
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    sf::Color textColor; 
    bool isHovered;
    bool isPressed;
    std::function<void()> onClick;

public:
    Button(float x, float y, float width, float height,
           const std::string& buttonText, sf::Font* font, unsigned int fontSize,
           const sf::Color& color, const std::string& name, VariableDatabase* db,
           const std::string& varName = "", std::function<void()> onClickFunc = nullptr,
           const sf::Color& textClr = sf::Color::Black);  
    
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    
    bool contains(float pointX, float pointY) const;
    void setOnClick(std::function<void()> onClickFunc);
    void setTextColor(const sf::Color& color); 
};

#endif
