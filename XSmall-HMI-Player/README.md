# XSmall-HMI SCADA Player

Проигрыватель SCADA-экранов с поддержкой визуальных объектов.

## Сборка
```bash
mkdir build
cd build
cp "C:/Libraries/SFML/bin/"*.dll .
cmake .. -G "MinGw Makefiles"
cmake --build . --j4

./HMI_Player.exe
