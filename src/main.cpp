#include "main.h"

// Port Assignment
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10
#define ARM_PORT 8
#define CLAW_PORT 20




// Tank Controls
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

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() 
{
	// autonomous functions calls go here
}