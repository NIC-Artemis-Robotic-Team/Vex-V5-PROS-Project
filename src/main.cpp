#include "main.h"

#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10
#define ARM_PORT 8
#define CLAW_PORT 20

void opcontrol() {

std::cout << "Tedst\n";

pros::Motor left_wheels (LEFT_WHEELS_PORT);
pros::Motor arm(ARM_PORT);
pros::Motor claw(CLAW_PORT);
pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
pros::Controller master (CONTROLLER_MASTER);

	while (true) {
		left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
		right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));

		arm.move(master.get_analog(ANALOG_LEFT_X));
		claw.move(master.get_analog(ANALOG_RIGHT_X));
		pros::delay(2);
	}
}
