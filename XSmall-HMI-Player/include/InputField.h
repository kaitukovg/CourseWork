#ifndef INPUTFIELD_H
#define INPUTFIELD_H

#include "VisualObject.h"
#include "VariableDatabase.h"
#include <SFML/Graphics.hpp>

class InputField : public VisualObject {
private:
    sf::RectangleShape background;
    sf::Text text;
    sf::Font* font;
    std::string variableName;
    bool isActive;
    std::string inputText;

public:
    InputField(float x, float y, float width, float height,
               sf::Font* font, unsigned int fontSize,
               const std::string& name, VariableDatabase* db,
               const std::string& varName = "");
    
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
    
    void setActive(bool active);
    bool contains(float pointX, float pointY) const;
};

#endif