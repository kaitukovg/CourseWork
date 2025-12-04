#include "HistoryGraph.h"
#include "logger.h"
#include <algorithm>

HistoryGraph::HistoryGraph(float x, float y, float width, float height,
                           const std::string& name, VariableDatabase* db,
                           const std::string& varName, size_t maxHistory,
                           const sf::Color& lineClr, const sf::Color& gridClr)
    : VisualObject(x, y, name, db), width(width), height(height), 
      variableName(varName), maxHistorySize(maxHistory),
      lineColor(lineClr), gridColor(gridClr) {
    
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::Transparent);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(1);
    
    // Подписываемся на изменения переменной для обновления графика
    if (!variableName.empty() && database) {
        database->subscribe(variableName, [this](double value) {
            this->update();
        });
    }
}

void HistoryGraph::draw(sf::RenderWindow& window) {
    window.draw(background);
    drawGrid(window);
    drawGraph(window);
}

void HistoryGraph::update() {
    // Обновление данных происходит через подписку на VariableDatabase
    // Визуальное обновление выполняется в drawGraph()
}

void HistoryGraph::drawGrid(sf::RenderWindow& window) {
    // Рисуем вертикальные линии сетки (4 секции)
    for (int i = 1; i < 4; ++i) {
        sf::Vertex verticalLine[] = {
            sf::Vertex(sf::Vector2f(x + i * width / 4, y), gridColor),
            sf::Vertex(sf::Vector2f(x + i * width / 4, y + height), gridColor)
        };
        window.draw(verticalLine, 2, sf::Lines);
    }
    
    // Рисуем горизонтальные линии сетки
    for (int i = 1; i < 4; ++i) {
        sf::Vertex horizontalLine[] = {
            sf::Vertex(sf::Vector2f(x, y + i * height / 4), gridColor),
            sf::Vertex(sf::Vector2f(x + width, y + i * height / 4), gridColor)
        };
        window.draw(horizontalLine, 2, sf::Lines);
    }
}

void HistoryGraph::drawGraph(sf::RenderWindow& window) {
    if (!variableName.empty() && database) {
        const auto& history = database->getHistory(variableName);
        if (history.size() > 1) {
            std::vector<sf::Vertex> lineVertices;
            
            // Находим минимальное и максимальное значения для масштабирования
            float maxVal = *std::max_element(history.begin(), history.end());
            float minVal = *std::min_element(history.begin(), history.end());
            float range = maxVal - minVal;
            if (range == 0) range = 1;  // Избегаем деления на ноль
            
            // Масштабируем точки графика под размеры виджета
            float xStep = width / (history.size() - 1);
            
            for (size_t i = 0; i < history.size(); ++i) {
                // Преобразуем значение в координаты Y (инвертируем ось Y - 0 вверху)
                float xPos = x + i * xStep;
                float yPos = y + height - ((history[i] - minVal) / range * height);
                lineVertices.push_back(sf::Vertex(sf::Vector2f(xPos, yPos), lineColor));
            }
            
            // Рисуем линию графика через все точки
            if (lineVertices.size() > 1) {
                window.draw(&lineVertices[0], lineVertices.size(), sf::LineStrip);
            }
        }
    }
}