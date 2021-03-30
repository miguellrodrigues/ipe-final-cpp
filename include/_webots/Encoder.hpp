//
// Created by miguel on 30/03/2021.
//

#ifndef IPE_FINAL_ENCODER_HPP
#define IPE_FINAL_ENCODER_HPP

#include <webots/PositionSensor.hpp>
#include <string>

using std::string;

namespace lib {
    class Encoder : public webots::PositionSensor {
    public:
        Encoder(const string &name, float wheel_radius, unsigned int sampling_rate);

        double getPosition();
    private:
        unsigned int sampling_rate;

        float wheel_radius;
    };
}

#endif //IPE_FINAL_ENCODER_HPP
