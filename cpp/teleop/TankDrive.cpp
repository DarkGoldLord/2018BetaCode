/*
 * TankDrive.cpp
 *
 *  Created on: Jan 27, 2018
 *      Author: Chris
 */

#include <subsys/ChassisFactory.h>
#include <teleop/TankDrive.h>
#include <teleop/TeleopControl.h>
#include <subsys/IChassis.h>

TankDrive::TankDrive() : IDrive()
{
    // Set the profile to cubic on the joysticks being used
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::TANK_DRIVE_LEFT_CONTROL,  IDragonGamePad::AXIS_PROFILE::CUBED );
	TeleopControl::GetInstance()->SetAxisProfile(TeleopControl::TANK_DRIVE_RIGHT_CONTROL, IDragonGamePad::AXIS_PROFILE::CUBED );
}

void TankDrive::Drive()
{
	ChassisFactory::GetIChassis()->SetTalonMode(DragonTalon::PERCENT);
	ChassisFactory::GetIChassis()->SetLeftRightMagnitudes( TeleopControl::GetInstance()->GetAxisValue( TeleopControl::TANK_DRIVE_LEFT_CONTROL ),
												           TeleopControl::GetInstance()->GetAxisValue( TeleopControl::TANK_DRIVE_RIGHT_CONTROL )	);
}

const char* TankDrive::GetIdentifier() const
{
    return "Tank Drive \n";
}

