//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_ROBOT_HPP
#define IPE_FINAL_ROBOT_HPP

#include "_webots/Controller.hpp"
#include "_webots/Wheel.hpp"
#include "_webots/Encoder.hpp"

#include <webots/Camera.hpp>

using lib::Controller;
using lib::Wheel;
using lib::Encoder;

using webots::Camera;

class Robot {
public:
    Robot(unsigned int sampling_rate, unsigned int wheels_count, float wheel_radius);

    void setVelocities(vector<double> velocities);

    int run();

    ~Robot();
private:
    Controller *controller;

    vector<Wheel *> wheels;
    vector<Encoder *> encoders;

    Camera *camera;

    unsigned int sampling_rate;
    unsigned int wheels_count;

    float wheel_radius;
};

#endif //IPE_FINAL_ROBOT_HPP
