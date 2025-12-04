#include "Line.h"

Line::Line(float x1, float y1, float x2, float y2, 
           const sf::Color& color, const std::string& name,
           VariableDatabase* db)
    : VisualObject(x1, y1, name, db), color(color) {
    
    line[0] = sf::Vertex(sf::Vector2f(x1, y1), color);
    line[1] = sf::Vertex(sf::Vector2f(x2, y2), color);
}

void Line::draw(sf::RenderWindow& window) {
    window.draw(line, 2, sf::Lines);
}