//
// Created by miguel on 30/03/2021.
//

#include "../include/Robot.hpp"

#include <vector>

using std::vector;

Robot::Robot(unsigned int sampling_rate, unsigned int wheels_count, float wheel_radius): sampling_rate(sampling_rate), wheels_count(wheels_count), wheel_radius(wheel_radius) {
    this->controller = new Controller(sampling_rate);

    this->wheels.reserve(wheels_count);
    this->encoders.reserve(wheels_count);

    for (unsigned int i = 0; i < wheels_count; ++i) {
        this->wheels.push_back(new Wheel(&"wheel" [i], wheel_radius));
        this->encoders.push_back(new Encoder(&"position_sensor" [i], wheel_radius, sampling_rate));
    }

    controller->step();
}

int Robot::run() {
    return controller->step();
}

void Robot::setVelocities(vector<double> velocities) {
    for (unsigned int i = 0; i < velocities.size(); ++i) {
        this->wheels.at(i)->setVelocity(velocities.at(i));
    }
}

Robot::~Robot() {
    delete this->controller;
}
