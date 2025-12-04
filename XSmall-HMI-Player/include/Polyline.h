#ifndef POLYLINE_H
#define POLYLINE_H

#include "VisualObject.h"
#include "VariableDatabase.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Polyline : public VisualObject {
private:
    std::vector<sf::Vertex> points;
    sf::Color color;
    std::string variableName;

public:
    Polyline(const std::vector<sf::Vector2f>& points, 
             const sf::Color& color, const std::string& name,
             VariableDatabase* db, const std::string& varName = "");
    
    void draw(sf::RenderWindow& window) override;
    void update() override;
    void updatePoints(const std::vector<sf::Vector2f>& newPoints);
};

#endif