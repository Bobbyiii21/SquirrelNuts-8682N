using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor_group leftside;
extern motor_group rightside;
extern controller Controller1;
extern motor Intakes;
extern motor Cata;
extern rotation CataRotation;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );