#include "main.h"

// Port Assignment
#define LEFT_WHEELS_PORT 1
#define RIGHT_WHEELS_PORT 10
// #define ARM_PORT 8
// #define CLAW_PORT 20


// ultrasonic port assignment
/*NOTE: The PING wire (orange) must always be assigned to an odd numbered Port
IE: 1,3,5,.... OR 'A','C','E'...
The ECHO wire (yellow) is then assigned to the next consecutive value
even number port*/

// sample initialization for ports values can be modified
#define ECHO 'B'  // Output - Send
#define PING 'A' // Input - Recieve



// Tank Controls
void opcontrol()
{

std::cout << "Tedst\n";
pros::ADIUltrasonic ultrasonic(PING,ECHO);
pros::Motor left_wheels (LEFT_WHEELS_PORT);
pros::Motor right_wheels (RIGHT_WHEELS_PORT, true); // This reverses the motor
pros::Controller master (CONTROLLER_MASTER);
	while (true)
	{
		int distance = ultrasonic.get_value();
			if (distance > 200 || distance <= 0 )
			{
				left_wheels = master.get_analog(ANALOG_LEFT_Y);
				right_wheels= master.get_analog(ANALOG_RIGHT_Y);
				pros::delay(50);
			}
			else
			{
				left_wheels = 0;
				right_wheels = 0;
				left_wheels = -45;
				right_wheels = -45;
			}
	}
}
