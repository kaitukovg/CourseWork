#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include <vector>
#include <memory>
#include <string>

class VariableDatabase;
class VisualObject;

namespace sf {
    class Font;
}

class SceneFactory {
public:
    static std::vector<std::unique_ptr<VisualObject>> loadFromFile(
        const std::string& filename, 
        VariableDatabase* db,
        sf::Font* font);
    
    // Создает тестовую сцену для демонстрации возможностей    
    static std::vector<std::unique_ptr<VisualObject>> createDemoScene(
        VariableDatabase* db,
        sf::Font* font);
};

#endif