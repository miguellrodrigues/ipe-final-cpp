//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_MOTOR_HPP
#define IPE_FINAL_MOTOR_HPP

#include <webots/Motor.hpp>
#include <string>

using std::string;

namespace lib {
    class Motor : public webots::Motor {
    public:
        Motor(const string &name, float wheel_radius, bool encoder);
    private:
        float wheel_radius;
    };
}


#endif //IPE_FINAL_MOTOR_HPP
