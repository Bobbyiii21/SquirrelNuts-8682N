/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftside             motor_group   18, 19
// rightside            motor_group   17, 16
// Controller1          controller
// Intakes              motor         10
// Cata                 motor         20
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void)
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void)
{
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void)
{
  // User control code here, inside the loop

#define pos_init 355.
#define middle_pos 292.

  int cata_mode = 0;

  while (1)
  {
    if (Controller1.ButtonL1.pressing())
    {
      Intakes.spin(forward, 100, percent);
    }
    else
      Intakes.stop();

    // if(Controller1.ButtonR1.pressing()){
    //   Cata.spin(fwd,100,percent);

    // }
    // else Cata.stop();

    // Get the velocity percentage of the left motor. (Axis2 + Axis1)
    int leftMotorSpeed =
        Controller1.Axis2.position() - Controller1.Axis1.position();
    // Get the velocity percentage of the right motor. (Axis2 - Axis1)
    int rightMotorSpeed =
        Controller1.Axis2.position() + Controller1.Axis1.position();

    int deadband = 5;
    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      leftside.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      leftside.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      rightside.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      rightside.setVelocity(rightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    leftside.spin(forward);
    rightside.spin(forward);

    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
   

    switch (cata_mode)
    {
    case 0:
      if (Controller1.ButtonR1.pressing())
      {
        Cata.spin(fwd, 100, percent);
      }
      else if (Controller1.ButtonDown.pressing())
      {
        cata_mode = 1;
      }
      else if (Controller1.ButtonLeft.pressing())
      {
        cata_mode = 2;
      }
      else
      {
        Cata.stop();
        printf("R1 not pressed\n");
      }
      break;
    case 1:
      if (Controller1.ButtonR1.pressing())
      {
        Cata.spin(fwd, 100, percent);
      }
      else if (Controller1.ButtonUp.pressing())
      {
        cata_mode = 0;
      }
      else if (Controller1.ButtonLeft.pressing())
      {
        cata_mode = 2;
      }
      else if (CataRotation.position(degrees) < (pos_init - 2) || CataRotation.position(degrees) > (pos_init + 2))
      {
        Cata.spin(forward, 50, percent);
      }
      else {
        Cata.stop();
        printf("Target reached\n");
      }
      break;
      
    case 2:
      if (Controller1.ButtonR1.pressing())
      {
        Cata.spin(fwd, 100, percent);
      } 
      else if (Controller1.ButtonUp.pressing())
      {
        cata_mode = 0;
      }
      else if (Controller1.ButtonDown.pressing())
      {
        cata_mode = 1;
      }
      else if (CataRotation.position(degrees) < (middle_pos - 10) || CataRotation.position(degrees) > (middle_pos + 10))
      {
        Cata.spin(forward, 50, percent);
      }
      else {
        Cata.stop();
        printf("Target reached\n");
      }
      break;

    }

    printf("CataRotation: %f\n", CataRotation.position(degrees));
    printf("CataMode: %d\n", cata_mode);

    if (CataRotation.position(degrees) > 360.)
    {
      CataRotation.setPosition(0., degrees);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
