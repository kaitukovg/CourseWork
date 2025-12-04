#include "VariableDatabase.h"
#include "logger.h"
#include <iostream>

VariableDatabase::VariableDatabase() {
    initializeDemoVariables();
}

void VariableDatabase::setVariable(const std::string& name, double value) {
    double oldValue = variables[name]; // Сохраняем старое значение для возможного отката
    
    // Обновляем текущее значение
    variables[name] = value;
    
    // Добавляем в историю изменений (для графиков)
    addToHistory(name, value);
    
    // Уведомляем всех подписчиков об изменениях
    if (subscribers.find(name) != subscribers.end()) {
        for (auto& callback : subscribers[name]) {
            callback(value);
        }
    }
    
    // Логируем изменения для отладки
    Logger::info("Variable '" + name + "' set to: " + std::to_string(value));
}

double VariableDatabase::getVariable(const std::string& name) const {
    auto it = variables.find(name);
    if (it != variables.end()) {
        return it->second;
    }
    return 0.0; // Возвращаем 0 для несуществующих переменных
}

bool VariableDatabase::variableExists(const std::string& name) const {
    return variables.find(name) != variables.end();
}

void VariableDatabase::addToHistory(const std::string& name, double value) {
    // Ограничиваем историю 100 последними значениями 
    historyVariables[name].push_back(value);
    
    if (historyVariables[name].size() > 100) {
        historyVariables[name].erase(historyVariables[name].begin());
    }
}

const std::vector<double>& VariableDatabase::getHistory(const std::string& name) const {
    // Возвращаем пустой вектор для несуществующей истории
    static std::vector<double> emptyHistory;
    auto it = historyVariables.find(name);
    if (it != historyVariables.end()) {
        return it->second;
    }
    return emptyHistory;
}

void VariableDatabase::subscribe(const std::string& variable, std::function<void(double)> callback) {
    // Добавляем callback в список подписчиков для указаннной переменной
    subscribers[variable].push_back(callback);
}

void VariableDatabase::initializeDemoVariables() {
    // Инициализация переменных для демо-режима
    setVariable("panel_status", 0.0);
    setVariable("temperature_value", 72.5);
    setVariable("setpoint_value", 65.0);
    setVariable("pressure_value", 1.2);
    
    // Создаем тестовую историю температуры для графиков
    for (int i = 0; i < 10; ++i) {
        setVariable("temperature_history", 70.0 + i * 0.5);
    }
}