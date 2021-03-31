//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_MOTORIZEDCAMERA_HPP
#define IPE_FINAL_MOTORIZEDCAMERA_HPP

#include <webots/Camera.hpp>
#include <webots/Motor.hpp>
#include <webots/PositionSensor.hpp>
#include <string>


using std::string;
using webots::Motor;
using webots::PositionSensor;

namespace lib {
    class MotorizedCamera : public webots::Camera {
    public:
        MotorizedCamera(const string &name);

        void setVelocity(double v);
    private:
        Motor *motor;

        PositionSensor *position_sensor;
    };
}

#endif //IPE_FINAL_MOTORIZEDCAMERA_HPP
