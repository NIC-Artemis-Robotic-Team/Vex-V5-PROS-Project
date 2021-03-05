#include "main.h"

// Port Assignment
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10
#define ARM_PORT 8
#define CLAW_PORT 20


// ultrasonic port assignment 
/*NOTE: The PING wire (orange) must always be assigned to an odd numbered Port
IE: 1,3,5,.... OR 'A','C','E'... 

The ECHO wire (yellow) is then assigned to the next consecutive value  
even number port*/

// sample initialization for ports values can be modified
#define ECHO 8 // Output - Send
#define PING 9 // Input - Recieve


// Tank Controls
void opcontrol()
{

std::cout << "Tedst\n";

pros::Motor left_wheels (LEFT_WHEELS_PORT);
pros::Motor arm(ARM_PORT);
pros::Motor claw(CLAW_PORT);
pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
pros::Controller master (CONTROLLER_MASTER);
pros::ADIUltrasonic ultrasonic(PING,ECHO); // ultrasonic sensor
	while (true)
	{
		// while the rover is greater than 100cm away from an object keep driving
		while (ultrasonic.get_value() > 100 )
		{
			left_wheels.move(master.get_analog(ANALOG_LEFT_Y));
			right_wheels.move(master.get_analog(ANALOG_RIGHT_Y));

			arm.move(master.get_analog(ANALOG_LEFT_X));
			claw.move(master.get_analog(ANALOG_RIGHT_X));
			pros::delay(2);
		}
	}
	
}