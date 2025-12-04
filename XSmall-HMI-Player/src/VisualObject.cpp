#include "VisualObject.h"

VisualObject::VisualObject(float x, float y, const std::string& name, VariableDatabase* db)
    : x(x), y(y), name(name), database(db) {}

void VisualObject::setPosition(float newX, float newY) {
    x = newX;
    y = newY;
}

std::string VisualObject::getName() const {
    return name;
}