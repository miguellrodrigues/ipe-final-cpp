//
// Created by miguel on 30/03/2021.
//
#include "../../include/_webots/MotorizedCamera.hpp"
#include "../../include/Numbers.hpp"

#include <webots/Camera.hpp>
#include <webots/Motor.hpp>

#define RAD_TO_DEG (180.0 / M_PI)
#define DEG_TO_RAD (M_PI / 180.0)

using webots::Camera;
using webots::Motor;

lib::MotorizedCamera::MotorizedCamera(const string &name, unsigned int sampling_rate) : Camera(name) {
    this->motor = new Motor(name + "_motor");
    this->position_sensor = new PositionSensor("camera_position_sensor");

    this->position_sensor->enable((int)sampling_rate);

    motor->setPosition(INFINITY);
    motor->setVelocity(.0);
}

void lib::MotorizedCamera::setVelocity(double v) {
    this->motor->setVelocity(v);
}

double lib::MotorizedCamera::getEncoderValue(bool rad) {
    if (rad) {
        return this->position_sensor->getValue();
    } else {
        return this->position_sensor->getValue() * RAD_TO_DEG;
    }
}