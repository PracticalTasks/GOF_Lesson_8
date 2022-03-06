#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:
    void Draw() const override;
    Plane* clone() override { return nullptr; };
    void ChangePlaneY(double dy) { yDirection += dy; }

};

