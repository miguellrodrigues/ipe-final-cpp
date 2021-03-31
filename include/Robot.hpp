//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_ROBOT_HPP
#define IPE_FINAL_ROBOT_HPP

#include "_webots/Controller.hpp"
#include "_webots/Wheel.hpp"
#include "_webots/Encoder.hpp"
#include "_webots/MotorizedCamera.hpp"
#include "ImageProc.hpp"

using lib::Controller;
using lib::Wheel;
using lib::Encoder;
using lib::MotorizedCamera;

using webots::Camera;

class Robot {
public:
    Robot(unsigned int sampling_rate, unsigned int wheels_count, float wheel_radius);

    int run();

    void setVelocities(const vector<double> &velocities);

    void setCameraVelocity(double v);

    cv::Mat getCameraImage();

    double getCameraPosition(bool rad = true);

    void turnCamera(double d);

    double getRotationAngle();

    void turn(double d);

    ~Robot();

private:
    Controller *controller;

    vector<Wheel *> wheels;
    vector<Encoder *> encoders;

    MotorizedCamera *camera;
};

#endif //IPE_FINAL_ROBOT_HPP
