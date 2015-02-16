
//--------------------------------Experimental Acceleration----------------------------//
					/*if (accSpeed.WhileHeld())
					{
						if (Xprev < Stick.GetX() && Stick.GetX() >= 0)
						{
								Xacc+= Xaxis / 10;
						}
						else if (Xprev > Stick.GetX() && Stick.GetX() <= 0)
						{
							Xacc-= Xaxis / 10;

						}
						else
						if (Xacc > 1)
							Xacc = 1;
						if (Xacc < -1)
							Xacc = -10;

						Xprev = Stick.GetX();
						robotDrive.MecanumDrive_Cartesian(Xacc, Yaxis/2, Zaxis/2.5);
					}*/

#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

class Robot: public SampleRobot
{

    // Channels for the wheels
    const static int frontLeftChannel	= 2;
    const static int rearLeftChannel	= 0;
    const static int frontRightChannel	= 1;
    const static int rearRightChannel	= 3;
    const static int motorChannel		= 4;
    const static int joystickChannel	= 0;
    DigitalInput topSwitch;
    DigitalInput bottomSwitch;
    Jaguar motor;
	RobotDrive robotDrive;	// robot drive system
	Joystick stick;
	bool trigger 						= stick.GetTrigger();
	float Xaxis 						= stick.GetX();
	float Yaxis						 	= stick.GetY();
	float Zaxis							= stick.GetZ();
	NetworkTable *table;
public:
	Robot() :
			//Piston(1,2),
			topSwitch(0),
			bottomSwitch(1),
			motor(motorChannel),
			robotDrive(frontLeftChannel, rearLeftChannel,
					   frontRightChannel, rearRightChannel),	// these must be initialized in the same order
			stick(joystickChannel)								// as they are declared above.

	{
		robotDrive.SetExpiration(0.1);
		robotDrive.SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);	// invert the left side motors
		robotDrive.SetInvertedMotor(RobotDrive::kRearLeftMotor, true);	// you may need to change or remove this to match your robot
		table = NetworkTable::GetTable("datatable");
	}

	void OperatorControl()
	{
		robotDrive.SetSafetyEnabled(false);
		while (IsOperatorControl() && IsEnabled())
		{
			bool top = topSwitch.Get();
			bool bottom = bottomSwitch.Get();

			table->PutBoolean("TopSwitch", top);
			table->PutBoolean("BottomSwitch", bottom);
			table->PutNumber("Xaxis", stick.GetX());

			if(top == true)
			{
				if(stick.GetRawButton(1) == true)
				{
					motor.SetSpeed(0);
				}
				else if(stick.GetRawButton(2) == true)
				{
					motor.SetSpeed(-2);
				}
				else
				{
					motor.SetSpeed(0);
				}
			}
			else if(bottom == true)
			{
				if(stick.GetRawButton(1) == true)
				{
					motor.SetSpeed(2);
				}
				else if(stick.GetRawButton(2) == true)
				{
					motor.SetSpeed(0);
				}
				else
				{
					motor.SetSpeed(0);
				}
			}
			else
			{
				if(stick.GetRawButton(1) == true)
				{
					motor.SetSpeed(2);
				}
				else if(stick.GetRawButton(2) == true)
				{
					motor.SetSpeed(-2);
				}
				else
				{
					motor.SetSpeed(0);
				}
			}

			robotDrive.MecanumDrive_Cartesian(stick.GetX()/2, stick.GetY()/2, stick.GetZ()/2.5);//Moves the motors when the stick moves
			Wait(0.005); // wait 5ms to avoid hogging CPU cycles
		}
	}
};
START_ROBOT_CLASS(Robot);

