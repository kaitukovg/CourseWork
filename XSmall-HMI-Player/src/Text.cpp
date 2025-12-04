#include "Text.h"
#include "logger.h"
#include <sstream>
#include <iomanip>

Text::Text(float x, float y, const std::string& content, 
           sf::Font* font, unsigned int size, const sf::Color& color,
           const std::string& name, VariableDatabase* db, 
           const std::string& varName, const std::string& format)
    : VisualObject(x, y, name, db), formatString(format), 
      variableName(varName), font(font) {
    
    text.setPosition(x, y);
    text.setFont(*font);
    text.setCharacterSize(size);
    text.setFillColor(color);
    
    if (variableName.empty()) {
        // Статический текст - просто устанавливаем строку
        text.setString(content);
    } else {
        // Динамический текст - настраиваем подписку на переменную
        if (format.empty()) {
            text.setString(content);
        } else {
            formatString = format; // Сохраняем формат для динамического обновления
        }
        
        if (database) {
            database->subscribe(variableName, [this](double value) {
                this->update();
            });
        }
        update(); // Первоначальное обновление
    }
}

void Text::draw(sf::RenderWindow& window) {
    window.draw(text);
}

void Text::update() {
    if (!variableName.empty() && database) {
        double value = database->getVariable(variableName);
        
        if (!formatString.empty()) {
            // Форматируем строку с использованием шаблона
            std::stringstream ss;
            size_t pos = formatString.find("%f");
            if (pos != std::string::npos) {
                // Заменяем %f на значение с одним знаком после запятой
                std::string before = formatString.substr(0, pos);
                std::string after = formatString.substr(pos + 2);
                ss << before << std::fixed << std::setprecision(1) << value << after;
                text.setString(ss.str());
            } else {
                // Если нет спецификатора формата, просто добавляем значение
                text.setString(formatString + std::to_string(value));
            }
        } else {
            // Без форматирования - просто преобразуем число в строку
            text.setString(std::to_string(value));
        }
    }
}

void Text::setString(const std::string& str) {
    text.setString(str);
}