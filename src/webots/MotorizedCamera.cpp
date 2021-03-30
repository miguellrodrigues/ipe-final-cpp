//
// Created by miguel on 30/03/2021.
//
#include "../../include/_webots/MotorizedCamera.hpp"

#include <webots/Camera.hpp>
#include <webots/Motor.hpp>

using webots::Camera;
using webots::Motor;

lib::MotorizedCamera::MotorizedCamera(const string &name) : Camera(name) {
    this->motor = new Motor(name + "_motor");

    motor->setPosition(INFINITY);
    motor->setVelocity(.0);
}

void lib::MotorizedCamera::setVelocity(double v) {
    this->motor->setVelocity(v);
}




