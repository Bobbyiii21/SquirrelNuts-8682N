#include "vex.h"
using namespace vex;
#define pos_init 355.
#define middle_pos 292.


double deg_remainder(double number){
    return fmod(number, 360);
};


// User Control code here. To have more space to write.
void usercontrol(void)
{
  // User control code here, inside the loop



  int cata_mode = 0;
  int auto_speed = 25;

  

  while (1)
  {
    double cata_pos = CataRotation.position(degrees);
    if (Controller1.ButtonL1.pressing())
    {
      Intakes.spin(forward, 100, percent);
    }
    else Intakes.stop();



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
      double kp = 0.5;
      double ki = 0.1;
      double kd = 0.1;
      double derivative;
      double previous_error = 0;
      double integral = 0;
      double integral_limit = 10;
      double max_pct = 100;

      if (Controller1.ButtonR1.pressing())
      {
        Cata.spin(fwd, 25, percent);
      }
      else if (Controller1.ButtonUp.pressing())
      {
        cata_mode = 0;
      }
      else if (Controller1.ButtonLeft.pressing())
      {
        cata_mode = 2;
      }
      else if (Distance.objectDistance(mm) > 28)
      {
        double error = 28 - Distance.objectDistance(mm);

        if (fabs(error) < 1)
        {
        double previous_error = 0;
        double integral = 0;
          break;
        }

        derivative = error - previous_error;
        integral = integral + ki * error;
        if (integral > integral_limit) integral = integral_limit;
        if (integral < -integral_limit) integral = -integral_limit;
        
        //clamp max speed to 100
        double speed = (kp * error) + (ki * integral) + (kd * derivative);

        if (speed > max_pct) speed = max_pct;
        if (speed < -max_pct) speed = -max_pct;

        Cata.spin(forward, speed, percent);
        previous_error = error;
        
      }
      else {
        Cata.stop();
        printf("Target reached\n");
      }
      break;
      
    case 2:
      double kp = 0.5;
      double ki = 0.1;
      double kd = 0.1;
      double derivative;
      double previous_error = 0;
      double integral = 0;
      double integral_limit = 10;
      double max_pct = 100;
      if (Controller1.ButtonR1.pressing())
      {
        Cata.spin(fwd, 25, percent);
      } 
      
      else if (Controller1.ButtonUp.pressing()){
        cata_mode = 0;
      }
      else if (Controller1.ButtonDown.pressing())
      {
        cata_mode = 1;
      }
      else if (Distance.objectDistance(mm) > 79)
      {
        double error = 79 - Distance.objectDistance(mm);

        if (fabs(error) < 1)
        {
        double previous_error = 0;
        double integral = 0;
          break;
        }

        derivative = error - previous_error;
        integral = integral + ki * error;
        if (integral > integral_limit) integral = integral_limit;
        if (integral < -integral_limit) integral = -integral_limit;
        
        //clamp max speed to 100
        double speed = (kp * error) + (ki * integral) + (kd * derivative);

        if (speed > max_pct) speed = max_pct;
        if (speed < -max_pct) speed = -max_pct;

        Cata.spin(forward, speed, percent);
        previous_error = error;
        
      }
      else {
        Cata.stop();
        printf("Target reached\n");
      }
      break;

    }

    printf("CataRotation: %f\n", deg_remainder(cata_pos));
    printf("CataMode: %d\n", cata_mode);
    printf("Distance: %f\n", Distance.objectDistance(mm));
   
     Brain.Screen.print("Distance: %f\n", Distance.objectDistance(mm));
     Brain.Screen.clearScreen();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}