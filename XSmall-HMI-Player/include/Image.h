#ifndef IMAGE_H
#define IMAGE_H

#include "VisualObject.h"
#include <SFML/Graphics.hpp>

class Image : public VisualObject {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float imgWidth, imgHeight;
    std::string imagePath;
    bool textureLoaded;

public:
    Image(float x, float y, float width, float height,
          const std::string& path, const std::string& name,
          VariableDatabase* db);
    
    void draw(sf::RenderWindow& window) override;
    void update() override {};
    
    bool loadTexture(const std::string& path);
};

#endif