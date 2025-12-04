#ifndef TEXT_H
#define TEXT_H

#include "VisualObject.h"
#include "VariableDatabase.h"
#include <SFML/Graphics.hpp>

class Text : public VisualObject {
private:
    sf::Text text;
    std::string formatString;
    std::string variableName;
    sf::Font* font;

public:
    Text(float x, float y, const std::string& content, 
         sf::Font* font, unsigned int size, const sf::Color& color,
         const std::string& name, VariableDatabase* db, 
         const std::string& varName = "", const std::string& format = "");
    
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void setString(const std::string& str);
};

#endif