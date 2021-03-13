#include "main.h"

// Port Assignment
#define LEFT_WHEELS_FRONT 10
#define RIGHT_WHEELS_FRONT 1
#define LEFT_WHEELS_BACK 9
#define RIGHT_WHEELS_BACK 2


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
pros::Motor left_wheels_f (LEFT_WHEELS_FRONT);
pros::Motor right_wheels_f (RIGHT_WHEELS_FRONT,true); // This reverses the motor
pros::Motor left_wheels_b(LEFT_WHEELS_BACK);
pros::Motor right_wheels_b(RIGHT_WHEELS_BACK, true); // reverses the motor
pros::Controller master (CONTROLLER_MASTER);


	while (true)
	{
		int distance = ultrasonic.get_value();
			if (distance > 200 || distance <= 0 )
			{
				left_wheels_f  =  master.get_analog(ANALOG_LEFT_Y);
				left_wheels_b = master.get_analog(ANALOG_LEFT_Y);
				right_wheels_f  = master.get_analog(ANALOG_RIGHT_Y);
				right_wheels_b = master.get_analog(ANALOG_RIGHT_Y);
				pros::delay(50);
			}
			else
			{
				left_wheels_f = left_wheels_b = 0;
				right_wheels_f = right_wheels_b = 0;
				left_wheels_f = -45;
				right_wheels_f = -45;
			}
	}
}