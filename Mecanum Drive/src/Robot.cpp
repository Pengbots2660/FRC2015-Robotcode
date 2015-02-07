#include "WPILib.h"

class Robot: public RobotCode
{

    // Channels for the wheels
    const static int frontLeftChannel	= 2;
    const static int rearLeftChannel	= 3;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 0;
    const static int joystickChannel	= 0;
	RobotDrive robotDrive;	// robot drive system
	Joystick stick;
	float Xaxis = stick.GetX();
	float Yaxis = stick.GetY();
	float Zaxis = stick.GetZ();
	DoubleSolenoid Piston;
	int POV = stick.GetPOV();
	const int button1 = 1;
	

public:
	Robot() :
			Piston(1,2),
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(joystickChannel)							// as they are declared above.
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
		robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
			if(stick.GetRawButton[(button1)] == true)//I doubt this [(button1)] thing will work, but it got eclipse to shut up about my errors
			{
				Piston.Set(DoubleSolenoid::kForward);
			}
			else if(stick.GetRawButton[(button1)] == false)//I doubt this [(button1)] thing will work, but it got eclipse to shut up about my errors
			{
				Piston.Set(DoubleSolenoid::kReverse);
			}

			robotDrive.MecanumDrive_Cartesian(stick.GetX()/2, stick.GetY()/2, stick.GetZ()/2.5);//Moves the motors when the stick moves
			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}

};

START_ROBOT_CLASS(Robot);
