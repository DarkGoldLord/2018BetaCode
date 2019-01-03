/*
 * TeleopDrive.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: jonah
 */

#include <subsys/ChassisFactory.h>
#include <subsys/IChassis.h>
#include <teleop/TeleopControl.h>
#include <teleop/TeleopDrive.h>

TeleopDrive::TeleopDrive() : IDrive()
{
    // Set the profile to cubic on the joysticks being used
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ROBOT_X_MAGNITUDE, IDragonGamePad::AXIS_PROFILE::CUBED );
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ROBOT_Y_MAGNITUDE, IDragonGamePad::AXIS_PROFILE::CUBED );
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::ROBOT_ROTATION_MAGNITUDE, IDragonGamePad::AXIS_PROFILE::CUBED );

}
void TeleopDrive::Drive()
{
	ChassisFactory::GetIChassis()->EnableCurrentLimiting(true);
	ChassisFactory::GetIChassis()->SetTalonMode( DragonTalon::PERCENT );
	//Set chassis power according to OI's inputs
	ChassisFactory::GetIChassis()->SetDriveMagnitudes(
	TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_X_MAGNITUDE ),
	TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_Y_MAGNITUDE ),
	TeleopControl::GetInstance()->GetAxisValue( TeleopControl::ROBOT_ROTATION_MAGNITUDE ));
}

const char* TeleopDrive::GetIdentifier() const
{
    return "Increased turn control at high speeds mode \n";
}

