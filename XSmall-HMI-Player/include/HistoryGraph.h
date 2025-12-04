#ifndef HISTORYGRAPH_H
#define HISTORYGRAPH_H

#include "VisualObject.h"
#include "VariableDatabase.h"
#include <SFML/Graphics.hpp>
#include <vector>

class HistoryGraph : public VisualObject {
private:
    float width, height;
    sf::RectangleShape background;
    std::string variableName;
    size_t maxHistorySize;
    sf::Color lineColor;
    sf::Color gridColor;

public:
    HistoryGraph(float x, float y, float width, float height,
                 const std::string& name, VariableDatabase* db,
                 const std::string& varName = "", 
                 size_t maxHistory = 50,
                 const sf::Color& lineClr = sf::Color::Blue,
                 const sf::Color& gridClr = sf::Color(200, 200, 200, 100));
    
    void draw(sf::RenderWindow& window) override;
    void update() override;
    
private:
    void drawGrid(sf::RenderWindow& window);
    void drawGraph(sf::RenderWindow& window);
};

#endif