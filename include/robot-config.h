using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor_group leftside;
extern motor_group rightside;
extern controller Controller1;
extern motor Cata1;
extern motor Cata2;
extern rotation CataRotation;
extern motor_group Cata;
extern distance Distance;
extern motor leftIntake;
extern motor rightIntake;
extern motor_group Intakes;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );