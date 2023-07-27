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
motor Intakes = motor(PORT10, ratio6_1, false);
motor Cata = motor(PORT20, ratio36_1, true);
rotation CataRotation = rotation(PORT13, false);

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