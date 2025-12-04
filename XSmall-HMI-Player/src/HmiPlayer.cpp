#include "HmiPlayer.h"
#include "SceneFactory.h"
#include "StateManager.h"
#include "logger.h"
#include <thread>
#include <chrono>

HmiPlayer::HmiPlayer() 
    : window(sf::VideoMode(1024, 768), "XSmall-HMI SCADA Player") {
    
    window.setFramerateLimit(60); // Ограничения 60 FPS для стабильности
}

bool HmiPlayer::initialize() {
    // Загружаем шрифт
    std::vector<std::string> fontPaths = {
        "../assets/fonts/helveticabold.ttf",
        "assets/fonts/helveticabold.ttf",
        "assets/fonts/arial.ttf",        
        "../../assets/fonts/helveticabold.ttf"
    };
    
    bool fontLoaded = false;
    for (const auto& path : fontPaths) {
        if (font.loadFromFile(path)) {
            Logger::info("Font loaded successfully from: " + path);
            fontLoaded = true;
            break;
        }
    }
    
    if (!fontLoaded) {
        Logger::error("Failed to load font from all possible paths");
        return false;
    }
    
    // Загружаем сохраненное состояние из файла saved_state.json
    StateManager stateManager;
    stateManager.loadState(database);
    
    // Создаем визуальные объекты
    objects = SceneFactory::createDemoScene(&database, &font);
    
    if (objects.empty()) {
        Logger::error("No objects created during initialization");
        return false;
    }
    
    Logger::info("HMI Player initialized with " + std::to_string(objects.size()) + " objects");
    return true;
}

void HmiPlayer::run() {
    StateManager stateManager;
    
     // Главный цикл приложения
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
        
        // Автосохранение каждые 30 секунд
        static sf::Clock saveClock;
        if (saveClock.getElapsedTime().asSeconds() > 30.0) {
            stateManager.saveState(database);
            saveClock.restart();
        }
        
        // Задержка для контроля частоты кадров
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
    
    // Сохраняем при закрытии
    stateManager.saveState(database);
}

void HmiPlayer::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        
        // Передаем события всем объектам для обработки
        for (auto& obj : objects) {
            obj->handleEvent(event, window);
        }
    }
}

void HmiPlayer::update() {
    static sf::Clock updateClock;

    // Обновляем объекты каждые 100 мс (10 раз в секунду)
    if (updateClock.getElapsedTime().asMilliseconds() > 100) {
        for (auto& obj : objects) {
            obj->update();
        }
        updateClock.restart();
    }
    
    // Умное обновление температуры - стремится к введенному нами значения setpoint 
    static sf::Clock demoClock;
    if (demoClock.getElapsedTime().asSeconds() > 0.2) { // Задается скорость изменения
        double currentTemp = database.getVariable("temperature_value");
        double setpoint = database.getVariable("setpoint_value");
        
        // Вычисляем разницу и плавно изменяем температуру
        double difference = setpoint - currentTemp;
        double change = 0.0;
        
        // Адаптивный шаг изменения: больше для больших разниц
        if (std::abs(difference) > 1.0) {
            change = (difference > 0) ? 0.2 : -0.2; // Шаг
        } else if (std::abs(difference) > 0.2) {
            change = difference * 0.5; // Пропорциональное изменение
        } else {
            change = difference * 0.8; // Медленное доведение до точного значения
        }
        
        double newTemp = currentTemp + change;
        database.setVariable("temperature_value", newTemp);
        database.addToHistory("temperature_history", newTemp);
        
        demoClock.restart();
    }
}

void HmiPlayer::render() {
    window.clear(sf::Color(16, 41, 79)); // Темно-синий фон
    
    for (auto& obj : objects) {
        obj->draw(window);
    }
    
    window.display();
}
