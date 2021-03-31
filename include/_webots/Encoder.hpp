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

        void setOffset(double o);

        double getPosition();

    private:
        double wheel_radius;
        double offset = .0;
    };
}

#endif //IPE_FINAL_ENCODER_HPP
