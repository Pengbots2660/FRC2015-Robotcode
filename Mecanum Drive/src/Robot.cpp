#include "WPILib.h"

/**
 * This is a demo program showing how to use Mecanum control with the RobotDrive class.
 */
class Robot: public SampleRobot
{

    // Channels for the wheels
    const static int frontLeftChannel	= 2;
    const static int rearLeftChannel	= 3;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 0;

    const static int joystickChannel	= 0;
    //Compressor comp;
    //DoubleSolenoid Piston;
	RobotDrive robotDrive;	// robot drive system
	Joystick stick = new Joystick(1,5,8);			// only joystick
	bool trigger = stick.(1);
	float Xaxis = stick.GetX();
	float Yaxis = stick.GetY();
	float Zaxis = stick.GetZ();

public:
	Robot() :
			//Piston(1,2),
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(0)							// as they are declared above.
	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);	// invert the left side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);	// you may need to change or remove this to match your robot
	}

	/**
	 * Runs the motors with Mecanum drive.
	 */
	void OperatorControl()
	{
		//compressor.Start();//Starts the compressor
		robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
        	// Use the joystick X axis for lateral movement, Y axis for forward movement, and Z axis for rotation.
        	// This sample does not use field-oriented drive, so the gyro input is set to zero.
			if (trigger == true){
				robotDrive.MecanumDrive_Cartesian(stick.GetX()/5, stick.GetY()/5, stick.GetZ()/5.5);
			}else if(trigger == false){
				robotDrive.MecanumDrive_Cartesian(stick.GetX()/2, stick.GetY()/2, stick.GetZ()/2.5);//Moves the motors when the stick moves
			}
			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}

};

START_ROBOT_CLASS(Robot);
