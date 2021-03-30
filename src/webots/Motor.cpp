//
// Created by miguel on 30/03/2021.
//

#include "../../include/webots/Motor.hpp"

#include <string>

using lib::Motor;

Motor::Motor(const string &name, float wheel_radius, bool encoder) : webots::Motor(name), wheel_radius(wheel_radius) {
    this->setVelocity(.0);
    this->setPosition(INFINITY);
}
