#include "main.h"

// Port Assignment
#define LEFT_WHEELS_FRONT 12
#define RIGHT_WHEELS_FRONT 11
#define LEFT_WHEELS_BACK 20
#define RIGHT_WHEELS_BACK 19

#define NUM_LEVELS 5

// ultrasonic port assignment
/*NOTE: The PING wire (orange) must always be assigned to an odd numbered Port
IE: 1,3,5,.... OR 'A','C','E'...
The ECHO wire (yellow) is then assigned to the next consecutive value
even number port*/

// sample initialization for ports values can be modified
#define ECHO 'B' // Output - Send
#define PING 'A' // Input - Recieve

// Tank Controls
void opcontrol()
{
    int levels[] = {10, 6, 4, 2, 1};

    pros::ADIUltrasonic ultrasonic(PING, ECHO);
    pros::Motor left_wheels_f(LEFT_WHEELS_FRONT);
    pros::Motor right_wheels_f(RIGHT_WHEELS_FRONT, true); // reverses the motor
    pros::Motor left_wheels_b(LEFT_WHEELS_BACK);
    pros::Motor right_wheels_b(RIGHT_WHEELS_BACK, true); // reverses the motor
    pros::Controller master(CONTROLLER_MASTER);

    // changes gearset for all drive motors
    left_wheels_f.set_gearing(pros::E_MOTOR_GEARSET_06);
    left_wheels_b.set_gearing(pros::E_MOTOR_GEARSET_06);
    right_wheels_b.set_gearing(pros::E_MOTOR_GEARSET_06);
    right_wheels_f.set_gearing(pros::E_MOTOR_GEARSET_06);

    int currentLevel = 4; // starting level

    int ultraSonicOn = 1; // ulstrasonic value set to true (1)

    while (true)
    {

        int distance = ultrasonic.get_value();
        // if button is pressed disable ultrasonic sensor
        if ((distance > 100 || distance <= 0) || ultraSonicOn == 0)
        {
            left_wheels_f = master.get_analog(ANALOG_LEFT_Y) / levels[currentLevel];
            left_wheels_b = master.get_analog(ANALOG_LEFT_Y) / levels[currentLevel];
            right_wheels_f = master.get_analog(ANALOG_RIGHT_Y) / levels[currentLevel];
            right_wheels_b = master.get_analog(ANALOG_RIGHT_Y) / levels[currentLevel];
            pros::delay(50);

            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) // US on
            {
                ultraSonicOn = 1;
            }

            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) // US off
            {
                ultraSonicOn = 0;
            }

            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) // gears down
            {
                currentLevel--;
                if (currentLevel < 0)
                {
                    currentLevel = 0;
                }
            }

            if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) // gears up
            {
                currentLevel++;
                if (currentLevel > NUM_LEVELS - 1)
                {
                    currentLevel = NUM_LEVELS - 1;
                }
            }

            // if a button is pressed, turn off ultrasonic
        }
        else
        {
            left_wheels_f = left_wheels_b = 0;
            right_wheels_f = right_wheels_b = 0;

            left_wheels_f = -40;
            right_wheels_f = -40;
            left_wheels_b = -40;
            right_wheels_b = -40;
        }
    }
}
