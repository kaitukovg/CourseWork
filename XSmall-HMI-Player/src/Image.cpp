#include "Image.h"
#include "logger.h"
#include <iostream>

Image::Image(float x, float y, float width, float height,
             const std::string& path, const std::string& name,
             VariableDatabase* db)
    : VisualObject(x, y, name, db), imgWidth(width), imgHeight(height),
      imagePath(path), textureLoaded(false) {
    
    std::cout << "Attempting to load image from: " << path << std::endl;
    textureLoaded = loadTexture(path);
    
    sprite.setPosition(x, y);
    if (textureLoaded) {
        // Масштабируем изображение под нужный размер
        float scaleX = width / sprite.getLocalBounds().width;
        float scaleY = height / sprite.getLocalBounds().height;
        sprite.setScale(scaleX, scaleY);
        std::cout << "Image loaded successfully: " << path << std::endl;
    } else {
        std::cout << "Failed to load image: " << path << std::endl;
    }
}

void Image::draw(sf::RenderWindow& window) {
    if (textureLoaded) {
        window.draw(sprite);
    } else {

        // Рисуем заглушку, если изображение не удалось загрузить
        sf::RectangleShape placeholder(sf::Vector2f(imgWidth, imgHeight));
        placeholder.setPosition(x, y);
        placeholder.setFillColor(sf::Color(200, 200, 200));
        placeholder.setOutlineColor(sf::Color::Black);
        placeholder.setOutlineThickness(2);
        window.draw(placeholder);
        
        // Текст "Image not found" при ошибке
        sf::Font font;
        // if (font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        if (font.loadFromFile("C:/projects/XSmall-HMI-Player/assets/fonts/couture.otf")) {
            sf::Text errorText;
            errorText.setFont(font);
            errorText.setString("Image not found");
            errorText.setCharacterSize(16);
            errorText.setFillColor(sf::Color::Black);
            errorText.setPosition(x + 10, y + imgHeight / 2 - 10);
            window.draw(errorText);
        }
    }
}

// Пытается загрузить текстуру из нескольких возможных путей
bool Image::loadTexture(const std::string& path) {
    // Пробуем несколько возможных путей
    std::vector<std::string> possiblePaths = {
        path,  // Оригинальный путь
        "../" + path,  // На уровень выше
        "../../" + path,  // На два уровня выше
        "C:/projects/XSmall-HMI-Player/" + path,  // Абсолютный путь
        "assets/images/logo.png",  // Просто от корня
        "../assets/images/logo.png" // От build папки
    };
    
    // Пробуем каждый путь
    for (const auto& testPath : possiblePaths) {
        std::cout << "Trying to load: " << testPath << std::endl;
        if (texture.loadFromFile(testPath)) {
            sprite.setTexture(texture);
            std::cout << "Successfully loaded from: " << testPath << std::endl;
            return true;
        }
    }
    
    Logger::warning("Could not load image from any path: " + path);
    return false;
}