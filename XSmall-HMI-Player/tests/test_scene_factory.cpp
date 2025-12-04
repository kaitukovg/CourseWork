#include <gtest/gtest.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "SceneFactory.h"
#include "VariableDatabase.h"
#include "VisualObject.h"  

class SceneFactoryTest : public ::testing::Test {
protected:
    VariableDatabase db;
    sf::Font font;
    
    void SetUp() override {
        // Пробуем несколько путей к шрифту
        std::vector<std::string> fontPaths = {
            "assets/fonts/helveticabold.ttf",
            "assets/fonts/arial.ttf",
            "../assets/fonts/helveticabold.ttf",
            "../../assets/fonts/helveticabold.ttf",
            "C:/Windows/Fonts/arial.ttf"
        };
        
        bool loaded = false;
        for (const auto& path : fontPaths) {
            if (font.loadFromFile(path)) {
                std::cout << "Тестовый шрифт загружен из: " << path << std::endl;
                loaded = true;
                break;
            }
        }
        
        if (!loaded) {
            std::cerr << "ВНИМАНИЕ: Не удалось загрузить тестовый шрифт!" << std::endl;
        }
    }
};

TEST_F(SceneFactiryrTest, CreateDemoScene) {
    // Проверяем, что шрифт загружен
    if (font.getInfo().family.empty()) {
        GTEST_SKIP() << "Шрифт не загружен, пропускаем тест CreateDemoScene";
    }
    
    auto objects = SceneFactory::createDemoScene(&db, &font);
    
    // Проверяем, что объекты созданы
    ASSERT_GT(objects.size(), 0) << "Должен быть создан хотя бы один объект";
    
    // Проверяем, что можем получить имена объектов
    for (const auto& obj : objects) {
        EXPECT_FALSE(obj->getName().empty()) << "Объект должен иметь имя";
    }
    
    // Проверяем основные типы объектов
    bool hasRectangle = false;
    bool hasText = false;
    bool hasButton = false;
    
    for (const auto& obj : objects) {
        std::string name = obj->getName();
        if (name.find("Rectangle") != std::string::npos ||
            name.find("Panel") != std::string::npos) hasRectangle = true;
        if (name.find("Text") != std::string::npos) hasText = true;
        if (name.find("Button") != std::string::npos) hasButton = true;
    }
    
    EXPECT_TRUE(hasRectangle) << "Должен быть хотя бы один прямоугольник";
    EXPECT_TRUE(hasText) << "Должен быть хотя бы один текст";
    EXPECT_TRUE(hasButton) << "Должна быть хотя бы одна кнопка";
    
    // Проверяем инициализацию переменных в базе данных
    EXPECT_TRUE(db.variableExists("temperature_value")) << "Должна существовать переменная temperature_value";
    EXPECT_TRUE(db.variableExists("pressure_value")) << "Должна существовать переменная pressure_value";
    EXPECT_TRUE(db.variableExists("setpoint_value")) << "Должна существовать переменная setpoint_value";
    EXPECT_TRUE(db.variableExists("panel_status")) << "Должна существовать переменная panel_status";

}
