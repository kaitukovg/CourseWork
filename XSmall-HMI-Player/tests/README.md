# XSmall-HMI SCADA Player TESTS

Тесты для прогрывателя SCADA-экранов с поддержкой визуальных объектов.

## Сборка
```bash
cd tests
mkdir test_build
cd test_build
cp "C:/Libraries/SFML/bin/"*.dll .
cp -r "/c/projects/XSmall-HMI-Player/assets" .
cmake .. -G "MinGw Makefiles"
cmake --build . --j4
./HMI_Tests.exe
