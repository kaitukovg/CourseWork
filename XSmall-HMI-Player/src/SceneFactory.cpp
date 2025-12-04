#include "SceneFactory.h"
#include "Rectangle.h"
#include "Text.h"
#include "Line.h"
#include "Polyline.h"
#include "InputField.h"
#include "Button.h"
#include "HistoryGraph.h"
#include "Image.h"
#include "logger.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


// Создаем полную демо-сцену для тестирования всех возможностей проекта
std::vector<std::unique_ptr<VisualObject>> SceneFactory::createDemoScene(
    VariableDatabase* db,
    sf::Font* font) {
    
    std::vector<std::unique_ptr<VisualObject>> objects;
    
    Logger::info("Creating demo SCADA scene");
    
    // 1. Панель статуса (прямоугольник) с условным форматированием по значению panel_status
    auto panel = std::make_unique<Rectangle>(20, 50, 500, 200, 
        sf::Color(173, 216, 230), "Status Panel", db, "panel_status");
    
    // Добавляем цветовые условие: разные цвета для разных статусов 
    panel->addCondition(0, sf::Color(124, 36, 179)); // Статус 0
    panel->addCondition(1, sf::Color{199, 24,88});   // Статус 1
    panel->addCondition(2, sf::Color{72, 146, 163}); // Статус 2
    panel->addCondition(3, sf::Color{176, 12, 160}); // Статус 3
    panel->addCondition(5, sf::Color{176, 80, 12});  // Статус 4
    panel->addCondition(6, sf::Color{22, 219, 219}); // Статус 5
    panel->addCondition(7, sf::Color::Magenta);      // Статус 6
    panel->addCondition(8, sf::Color::Black);        // Статус 7
    panel->addCondition(9, sf::Color::Red);          // Статус 8
    objects.push_back(std::move(panel));             // Статус 10
    
    // 2. Текст температуры с динамическим обновлением
    auto tempText = std::make_unique<Text>(75, 70, "Temperature: ", 
        font, 40, sf::Color::White, "Temperature Text", db, 
        "temperature_value", "Temperature:  ");
    objects.push_back(std::move(tempText));
    
    // 3. Текст давления
    auto pressureText = std::make_unique<Text>(150, 125, "Pressure: ",
        font, 25, sf::Color::White, "Pressure Text", db,
        "pressure_value", "Pressure:  ");
    objects.push_back(std::move(pressureText));
    
    // 4. Текст уставки Setpoint
    auto setpointText = std::make_unique<Text>(170, 160, "Setpoint: ",
        font, 20, sf::Color::White, "Setpoint Text", db,
        "setpoint_value", "Setpoint: ");
    objects.push_back(std::move(setpointText));
    
    // 5. Поле ввода для уставки температуры
    auto inputField = std::make_unique<InputField>(40, 200, 200, 40,
        font, 23, "Setpoint Input", db, "setpoint_value");
    objects.push_back(std::move(inputField));
    
    // 6. Кнопка Apply с обработчиком клика
    auto applyButton = std::make_unique<Button>(250, 200, 100, 40,
        "Apply", font, 23, sf::Color(45, 15, 127), "Apply Button", db,
        "", []() { Logger::info("Apply button clicked"); },
        sf::Color::White);  
    objects.push_back(std::move(applyButton));
    
    // 7. Линии-разделители
    auto line = std::make_unique<Line>(0, 280, 4200, 280, 
        sf::Color::White, "Separator Line", db);
    objects.push_back(std::move(line));

    auto line1 = std::make_unique<Line>(0, 285, 4200, 285, 
        sf::Color::White, "Separator Line", db);
    objects.push_back(std::move(line1));

    auto line2 = std::make_unique<Line>(0, 290, 4200, 290, 
        sf::Color::White, "Separator Line", db);
    objects.push_back(std::move(line2));
    
    // 8.1 Прямоугольник для лучшей видимости графика
    auto panel1 = std::make_unique<Rectangle>(20, 350, 400, 200, 
        sf::Color{0, 0, 0}, "Graph Panel", db, "graph_status");
    objects.push_back(std::move(panel1));
    
    // 8. График истории температуры
    auto graph = std::make_unique<HistoryGraph>(20, 250+100, 400, 200,
        "Temperature Graph", db, "temperature_history", 50, sf::Color{0, 255, 26});
    objects.push_back(std::move(graph));
    // 9. Изображение
    auto image = std::make_unique<Image>(720, 330, 350*0.5, 437*0.5,
        "assets/images/logo.png", "Logo Image", db);
    objects.push_back(std::move(image));
    
    // 10. Кнопка изменения статуса панели
    auto statusButton = std::make_unique<Button>(450, 340+20, 180, 50,
        "Change Color", font, 28, sf::Color(231, 214, 191), "Change Color", db,
        "", [db]() {
            static int status = 0;
            status = (status + 1) % 10;  // Циклическое переключение 0-9
            db->setVariable("panel_status", static_cast<double>(status));
            Logger::info("Panel status toggled to: " + std::to_string(status));
        },
        sf::Color{10, 35, 79});  
    objects.push_back(std::move(statusButton));
    
    // 11. Кнопка увеличения температуры 
    auto tempUpButton = std::make_unique<Button>(450, 400+20, 80, 30,
        "Temp +", font, 22, sf::Color(217, 72, 28), "Temp Increase", db,
        "", [db]() {
            double current = db->getVariable("temperature_value");
            db->setVariable("temperature_value", current + 1.0);
            Logger::info("Temperature increased to: " + std::to_string(current + 1.0));
        },
        sf::Color::White);
    objects.push_back(std::move(tempUpButton));
    
    // 12. Кнопка уменьшения температуры
    auto tempDownButton = std::make_unique<Button>(540, 400+20, 80, 30,
        "Temp -", font, 22, sf::Color(0, 178, 232), "Temp Decrease", db,
        "", [db]() {
            double current = db->getVariable("temperature_value");
            db->setVariable("temperature_value", current - 1.0);
            Logger::info("Temperature decreased to: " + std::to_string(current - 1.0));
        },
        sf::Color::White);  
    objects.push_back(std::move(tempDownButton));
    
    // 13. Кнопка увеличения давления 
    auto pressureUpButton = std::make_unique<Button>(450, 450+20, 80, 30,
        "Press +", font, 14, sf::Color(143, 0, 232), "Pressure Increase", db,
        "", [db]() {
            double current = db->getVariable("pressure_value");
            db->setVariable("pressure_value", current + 0.5);
            Logger::info("Pressure increased to: " + std::to_string(current + 0.1));
        },
        sf::Color::White);
    objects.push_back(std::move(pressureUpButton));

    // 14. Кнопка уменьшения давления 
    auto pressureDownButton = std::make_unique<Button>(540, 450+20, 80, 30,
        "Press -", font, 14, sf::Color(179, 73, 245), "Pressure Decrease", db,
        "", [db]() {
            double current = db->getVariable("pressure_value");
            db->setVariable("pressure_value", current - 0.5);
            Logger::info("Pressure decreased to: " + std::to_string(current - 0.1));
        },
        sf::Color::White);
    objects.push_back(std::move(pressureDownButton));
    
    // 15. Заголовок системы
    auto titleText = std::make_unique<Text>(550, 20, "XSmall HMI Player", 
        font, 60, sf::Color{249, 250, 197}, "System Title", db);
    objects.push_back(std::move(titleText));
    
    auto subtitleText = std::make_unique<Text>(650, 90, "SCADA System", 
        font, 40, sf::Color::White, "System Subtitle", db);
    objects.push_back(std::move(subtitleText));

    Logger::info("Demo scene created with " + std::to_string(objects.size()) + " objects");
    
    return objects;
}