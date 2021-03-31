//
// Created by miguel on 31/03/2021.
//

#ifndef IPE_FINAL_NUMBERS_HPP
#define IPE_FINAL_NUMBERS_HPP

class Numbers {
public:
    static double normalizeRadian(double r) {
        return atan2(sin(r), cos(r));
    }

    static double constrain(double x, double sat) {
        if (x > sat) {
            return sat;
        } else if (x < -sat) {
            return -sat;
        } else {
            return x;
        }
    }
};

#endif //IPE_FINAL_NUMBERS_HPP
