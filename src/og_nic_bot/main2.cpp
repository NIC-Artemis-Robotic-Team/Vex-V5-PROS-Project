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


int max_velocity = 100;
int R1_Pressed = master.get_digital(DIGITAL_R1);
int L1_Pressed = master.get_digital(DIGITAL_L1);

bool R1_Registered = false;
bool L1_Registered = false;

while (true)
	{
		// stop the rover before it collides with an object moving forward.
		int distance = ultrasonic.get_value();
			// if restrictions are not exceeded, then allow for manual control
			if (distance > 200 || distance <= 0 )
			{
					// if R1 is pressed
					if (R1_Pressed)
					{
						// after R1 is released
						if (R1_Registered== false)
						// increase by 5 rpm each press
						max_velocity += 5;
						// set max limit to 100% velocity
						if(max_velocity > 100)
							max_velocity = 100;

						R1_Registered = true;
					}
					else
						R1_Registered = false;

					// decrease wheel speed up to min using L1
					if (L1_Pressed)
					{
							// after L1 is released
							if (L1_Registered == false)
							max_velocity -= 5;
							// set lower limit to 50% velocity
							if(max_velocity < 50)
								max_velocity = 50;

							L1_Registered = true;
						}
						else
							L1_Registered = false;

					left_wheels = (master.get_analog(ANALOG_LEFT_Y) * max_velocity / 100);
					right_wheels = (master.get_analog(ANALOG_RIGHT_Y) * max_velocity / 100);
					pros::delay(50);

			}
			// otherwise stop the rover and back up 45 rotations on the motor
			else
			{
				left_wheels = 0;
				right_wheels = 0;
				left_wheels = -45;
				right_wheels = -45;
			}
	}
}