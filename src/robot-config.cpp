#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftsideMotorA = motor(PORT18, ratio6_1, false);
motor leftsideMotorB = motor(PORT19, ratio6_1, false);
motor_group leftside = motor_group(leftsideMotorA, leftsideMotorB);
motor rightsideMotorA = motor(PORT17, ratio6_1, true);
motor rightsideMotorB = motor(PORT16, ratio6_1, true);
motor_group rightside = motor_group(rightsideMotorA, rightsideMotorB);
controller Controller1 = controller(primary);
motor Cata1 = motor(PORT20, ratio36_1, true);
motor Cata2 = motor(PORT12, ratio36_1, false);
rotation CataRotation = rotation(PORT13, false);
distance Distance = distance(PORT8);
motor leftIntake = motor(PORT9);
motor rightIntake = motor(PORT10, true);
motor_group Intakes = motor_group(leftIntake, rightIntake);
//Cata Motor Group
motor_group Cata = motor_group(Cata1, Cata2);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  CataRotation.resetPosition();
}