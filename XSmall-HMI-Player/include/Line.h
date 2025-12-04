#ifndef LINE_H
#define LINE_H

#include "VisualObject.h"
#include <SFML/Graphics.hpp>

class Line : public VisualObject {
private:
    sf::Vertex line[2];
    sf::Color color;

public:
    Line(float x1, float y1, float x2, float y2, 
         const sf::Color& color, const std::string& name,
         VariableDatabase* db);
    
    void draw(sf::RenderWindow& window) override;
    void update() override {};
};

#endif