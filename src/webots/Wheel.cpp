//
// Created by miguel on 30/03/2021.
//

#include "../../include/_webots/Wheel.hpp"

#include <string>

using lib::Wheel;

Wheel::Wheel(const string &name, float wheel_radius) : webots::Motor(name), wheel_radius(wheel_radius) {
    this->setVelocity(.0);
    this->setPosition(INFINITY);
}
