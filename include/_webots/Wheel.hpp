//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_WHEEL_HPP
#define IPE_FINAL_WHEEL_HPP

#include <webots/Motor.hpp>
#include <string>

using std::string;

namespace lib {
    class Wheel : public webots::Motor {
    public:
        Wheel(const string &name, float wheel_radius);

    private:
        float wheel_radius;
    };
}


#endif //IPE_FINAL_WHEEL_HPP
