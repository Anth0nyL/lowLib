#include "pros/motors.h"
#define _CHASSIS_H
#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS
#include "api.h"


void leftdrive(int vel1, int dist1) {
    pros::c::motor_move(1, vel1*127/100);
    pros::c::motor_move(2, vel1*127/100);
    pros::c::motor_move(3, vel1*127/100);
}

void rightdrive(int vel2, int dist2) {
    pros::c::motor_move(4, vel2*127/100);
    pros::c::motor_move(5, vel2*127/100);
    pros::c::motor_move(6, vel2*127/100);
}
 
void straight(int vel3, int dist3) {
    leftdrive(vel3, dist3);
    rightdrive(vel3, dist3);
}

void move(int intitialvel, int dist) {
    double kP = 0.5;
    double kI = 0.1;
    double kD = 0.1;
    int prevError = 0;
    while(true) {
        double error = dist - pros::c::motor_get_position(1);
        double integral = integral + error;
        if (error == 0) {
            integral = 0;
        }
        
        int derivative = error - prevError;
        prevError = error;
        straight(error*kP+integral*kI+derivative*kD, dist);
        pros::c::delay(15);  
    }
}
