#include "Polyline.h"
#include "logger.h"

Polyline::Polyline(const std::vector<sf::Vector2f>& points, 
                   const sf::Color& color, const std::string& name,
                   VariableDatabase* db, const std::string& varName)
    : VisualObject(points.empty() ? 0 : points[0].x, 
                   points.empty() ? 0 : points[0].y, name, db), 
      color(color), variableName(varName) {
    
    // Инициализируем массив вершин
    for (const auto& point : points) {
        this->points.push_back(sf::Vertex(point, color));
    }
    
    // Подписываемся на изменения переменной для динамического обновления
    if (!variableName.empty() && database) {
        database->subscribe(variableName, [this](double value) {
            this->update();
        });
    }
}

void Polyline::draw(sf::RenderWindow& window) {
    if (points.size() > 1) {
        // Рисуем ломаную линию через все точки
        window.draw(&points[0], points.size(), sf::LineStrip);
    }
}

void Polyline::update() {
    if (!variableName.empty() && database) {
        const auto& history = database->getHistory(variableName);
        if (history.size() > 1) {
            points.clear();
            
            // Масштабируем исторические данные для отображения
            float maxVal = *std::max_element(history.begin(), history.end());
            float minVal = *std::min_element(history.begin(), history.end());
            float range = maxVal - minVal;
            if (range == 0) range = 1; // Избегаем деления на ноль
            
            // Фиксированные размеры для графика (можно сделать параметрами)
            float xStep = 400.0f / (history.size() - 1);
            float yScale = 200.0f / range;
            
            // Преобразуем значения истории в координаты точек
            for (size_t i = 0; i < history.size(); ++i) {
                float x = 20 + i * xStep;
                float y = 420 - (history[i] - minVal) * yScale;  // Инвертируем ось Y
                points.push_back(sf::Vertex(sf::Vector2f(x, y), color));
            }
        }
    }
}

void Polyline::updatePoints(const std::vector<sf::Vector2f>& newPoints) {
    points.clear();
    for (const auto& point : newPoints) {
        points.push_back(sf::Vertex(point, color));
    }
}