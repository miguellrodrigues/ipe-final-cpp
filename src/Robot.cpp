//
// Created by miguel on 30/03/2021.
//

#include "../include/Robot.hpp"

#include "../include/webots/Motor.hpp"

using lib::Motor;

Robot::Robot(unsigned int sampling_rate, unsigned int wheels, float wheel_radius): sampling_rate(sampling_rate), wheels(wheels), wheel_radius(wheel_radius) {

}
