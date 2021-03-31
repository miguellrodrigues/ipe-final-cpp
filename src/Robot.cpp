//
// Created by miguel on 30/03/2021.
//

#include "../include/Robot.hpp"
#include "../include/Numbers.hpp"

#include <vector>
#include <iostream>
#include <cmath>

#define DEG_TO_RAD (M_PI / 180.0)

using std::vector;

using std::cout;
using std::endl;
using std::to_string;

Robot::Robot(unsigned int sampling_rate, unsigned int wheels_count, float wheel_radius) : sampling_rate(sampling_rate),
                                                                                          wheels_count(wheels_count),
                                                                                          wheel_radius(wheel_radius) {
    this->controller = new Controller(sampling_rate);
    this->camera = new MotorizedCamera("camera", sampling_rate);

    this->camera->enable((int) sampling_rate);

    this->wheels.reserve(wheels_count);
    this->encoders.reserve(wheels_count);

    for (unsigned int i = 0; i < wheels_count; ++i) {
        this->wheels.push_back(new Wheel("wheel" + to_string(i), wheel_radius));
        this->encoders.push_back(new Encoder("position_sensor" + to_string(i), wheel_radius, sampling_rate));
    }

    controller->step();

    this->encoders.at(0)->setOffset(this->encoders.at(0)->getPosition());
    this->encoders.at(1)->setOffset(this->encoders.at(1)->getPosition());
}

int Robot::run() {
    return controller->step();
}

void Robot::setVelocities(const vector<double> &velocities) {
    for (unsigned int i = 0; i < velocities.size(); ++i) {
        this->wheels.at(i)->setVelocity(velocities.at(i));
    }
}

Robot::~Robot() {
    this->wheels.clear();
    this->encoders.clear();

    delete this->camera;
    delete this->controller;
}

void Robot::setCameraVelocity(double v) {
    this->camera->setVelocity(v);
}

Mat Robot::getCameraImage() {
    return ImageProc::processCameraImage(camera->getHeight(), camera->getWidth(), camera->getImage());
}

double Robot::getCameraPosition(bool rad) {
    return this->camera->getEncoderValue(rad);
}


void Robot::turnCamera(double d) {
    double r = -d * DEG_TO_RAD;

    double start_angle = this->camera->getEncoderValue();
    double angle_error = r - (this->camera->getEncoderValue() - start_angle);

    while (abs(angle_error) > .001 && run() != -1) {
        angle_error = r - (this->camera->getEncoderValue() - start_angle);

        double u = Numbers::constrain(angle_error * 0.6, 2);
        this->setCameraVelocity(u);
    }
}

double Robot::getRotationAngle() {
    double left_w = this->encoders.at(0)->getPosition();
    double right_w = this->encoders.at(1)->getPosition();

    double phi = (.028 / .1653) * (right_w - left_w);

    return Numbers::normalizeRadian(phi * 26.981325865);
}

void Robot::turn(double d) {
    double r = -d * DEG_TO_RAD;

    double start_angle = this->getRotationAngle();
    double angle_error = r - (this->getRotationAngle() - start_angle);

    while (abs(angle_error) > .002 && this->run() != -1) {
        angle_error = r - (this->getRotationAngle() - start_angle);

        double u = Numbers::constrain(angle_error * 2, 10);
        this->setVelocities({-u, u});
    }
}
