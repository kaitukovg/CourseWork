#ifndef VARIABLEDATABASE_H
#define VARIABLEDATABASE_H

#include <unordered_map>
#include <string>
#include <functional>
#include <vector>
#include <memory>

// Центральное хранилице переменных SCADA-системы 

class VariableDatabase {
private:
    // Основное хранилище переменных
    std::unordered_map<std::string, double> variables;
    
    // История изменений для каждой переменной (используется для графиков)
    std::unordered_map<std::string, std::vector<double>> historyVariables;
    
    // Подписчики на изменения переменных: имя переменной -> список callback-функций
    std::unordered_map<std::string, std::vector<std::function<void(double)>>> subscribers;

public:
    VariableDatabase();
    
    // Устанавливает значение и уведомляет подписчиков
    void setVariable(const std::string& name, double value);
    
    // Возвращает значение переменной
    double getVariable(const std::string& name) const;
    
    // Проверяет существование переменной
    bool variableExists(const std::string& name) const;
    
    // Добавляет значение в историю (автоматически обрезается до 100 значений)
    void addToHistory(const std::string& name, double value);
    
    // Возвращает историю изменений переменной
    const std::vector<double>& getHistory(const std::string& name) const;
    
    // Подписывает callback на изменения переменной
    void subscribe(const std::string& variable, std::function<void(double)> callback);
    
    // Инициализирует тестовые переменные для демо-режима
    void initializeDemoVariables();
};

#endif