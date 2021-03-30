//
// Created by miguel on 30/03/2021.
//

#include "../include/Robot.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    Robot robot(
            16,
            2,
            .032
    );

    while (robot.run() != -1) {
        cout << "Hello ! " << endl;
    }

    return 0;
}