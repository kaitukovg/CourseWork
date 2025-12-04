#include "HmiPlayer.h"
#include "logger.h"

int main() {
    Logger::info("Starting XSmall-HMI SCADA Player...");
    
    HmiPlayer player;
    
    if (!player.initialize()) {
        Logger::error("Failed to initialize HMI Player");
        return -1;
    }
    
    Logger::info("HMI Player initialized successfully");
    player.run(); // Запускаем главный цикл
    
    return 0;
}