#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

/**
 * Простая система логирования с тремя уровнями:
 * - INFO: Информационные сообщения
 * - WARNING: Предупреждения
 * - ERROR: Критические ошибки
 * 
 * Все сообщения выводятся в консоль с соответствующими префиксами.
 */

class Logger {
public:
    static void info(const std::string& message) {
        std::cout << "[INFO] " << message << std::endl;
    }
    
    static void error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }
    
    static void warning(const std::string& message) {
        std::cout << "[WARNING] " << message << std::endl;
    }
};

#endif