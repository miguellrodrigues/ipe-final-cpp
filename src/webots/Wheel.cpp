//
// Created by miguel on 30/03/2021.
//

#include "../../include/_webots/Wheel.hpp"

#include <string>

using lib::Wheel;

Wheel::Wheel(const string &name) : webots::Motor(name) {
    this->setVelocity(.0);
    this->setPosition(INFINITY);
}