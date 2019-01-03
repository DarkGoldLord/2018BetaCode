/*
 * TurnAngle.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: jonah
 */

//Includes
#include <cmath>
#include <frc/SmartDashboard/SmartDashboard.h>
//Team302 includes
#include <auton/TurnAngle.h>
#include <auton/PrimitiveFactory.h>
#include <subsys/IChassis.h>
#include <subsys/ChassisFactory.h>
#include <utils/LimitValue.h>

TurnAngle::TurnAngle() :
		m_chassis(ChassisFactory::GetIChassis()),
		m_lift(new LiftElevator()),
		m_targetAngle(0.0),
		m_targetDistance(0.0),
		m_targetSpeed(0.0),
		m_leftSpeed(0.0),
		m_rightSpeed(0.0),
		m_minTimeout(1),
		m_maxTimeout(3),
		m_speedMultiplier(0.0),
		m_lastAngle(0.0),
		m_isDone(false)
{
}

void TurnAngle::Init(PrimitiveParams* params) {
	m_isDone = false;
	m_chassis->SetTalonMode(DragonTalon::PERCENT);
	m_targetAngle = m_chassis->GetTargetHeading() + params->GetHeading();
	m_targetDistance = m_chassis->GetDistance();
	m_chassis->SetTargetHeading(m_targetAngle);
//	frc::SmartDashboard::PutNumber("TurnAngle target heading: ", m_targetAngle);
//	m_speedMultiplier = std::abs(params->GetDriveSpeed() * TURN_ANGLE_SPEED_MULTIPLIER);
	m_speedMultiplier = TURN_ANGLE_SPEED_MULTIPLIER;
//	printf("TURN ANGLE INIT!\n");

	m_chassis->EnableBrakeMode(false);

	m_minTimeout = 1;
	m_maxTimeout = 3.5;

//	frc::SmartDashboard::PutNumber("Target Speed For Turning", m_speedMultiplier);
//	frc::SmartDashboard::PutNumber("Target Angle For Turning", m_targetAngle);

	//Set target speeds for left and right to rotate. Left side is negated to spin different directions at same speed
//	m_chassis->SetVelocityParams(kP, kI, kD, kF, m_leftSpeed, m_rightSpeed); // JW updated
//  SmartDashboard::PutNumber("targetSpeed" , m_targetSpeed);
	m_lift->Init(params);
}

void TurnAngle::Run() //best method ever. Does nothing, and should do nothing... NOT ANYMORE, BUDDY!
{
	float deltaAngle = m_targetAngle - m_chassis->GetHeading();
	m_leftSpeed = deltaAngle * m_speedMultiplier;
	m_rightSpeed = -deltaAngle * m_speedMultiplier;

	float distanceError = m_chassis->GetDistance() - m_targetDistance;
//	frc::SmartDashboard::PutNumber("turn distance error: ", distanceError);
//	frc::SmartDashboard::PutNumber("turn m_leftSpeed before dist correction", m_leftSpeed);
//	frc::SmartDashboard::PutNumber("turn m_rightSpeed before dist correction", m_rightSpeed);
	frc::SmartDashboard::PutNumber("Current target heading drive", ChassisFactory::GetIChassis()->GetTargetHeading());
	frc::SmartDashboard::PutNumber("real heading... :(", ChassisFactory::GetIChassis()->GetHeading());

	m_leftSpeed -= distanceError * 0.1;
	m_rightSpeed -= distanceError * 0.1;

	if (deltaAngle > 0) {
		m_leftSpeed += MINIMUM_SPEED;
		m_rightSpeed -= MINIMUM_SPEED;
	} else {
		m_leftSpeed -= MINIMUM_SPEED;
		m_rightSpeed += MINIMUM_SPEED;
	}

//	frc::SmartDashboard::PutNumber("Run left speed", m_leftSpeed);
//	frc::SmartDashboard::PutNumber("Run right speed", m_rightSpeed);


//	m_leftSpeed = LimitValue::ForceInRange(m_leftSpeed, -0.8, 0.8);
//	m_rightSpeed = LimitValue::ForceInRange(m_rightSpeed, -0.8, 0.8);

	m_chassis->SetVelocityParams(PROPORTIONAL_COEFF, INTREGRAL_COEFF, DERIVATIVE_COEFF, FEET_FORWARD_COEFF, m_leftSpeed, m_rightSpeed);

	m_lift->Run();
	m_minTimeout -= IPrimitive::LOOP_LENGTH;
	m_maxTimeout -= IPrimitive::LOOP_LENGTH;
}

bool TurnAngle::IsDone() {
	if (!m_isDone) {
		float absDeltaAngle = std::abs(m_targetAngle - m_chassis->GetHeading());
		if (absDeltaAngle < ANGLE_THRESH) {
			m_isDone = true;
			m_lastAngle = m_targetAngle;
			m_chassis->SetTalonMode(DragonTalon::PERCENT);
			m_chassis->SetLeftRightMagnitudes( m_leftSpeed, m_rightSpeed );
		}
	}
	return (m_isDone && m_minTimeout < (IPrimitive::LOOP_LENGTH / 2)) || m_maxTimeout < (IPrimitive::LOOP_LENGTH / 2);
}


void TurnAngle::SetTargetAngle
(
    double      angle
)
{
    m_isDone = false;
    m_chassis->SetTalonMode(DragonTalon::PERCENT);
    m_targetAngle = m_chassis->GetTargetHeading() + angle;
    m_targetDistance = m_chassis->GetDistance();
    m_chassis->SetTargetHeading(m_targetAngle);
    m_speedMultiplier = TURN_ANGLE_SPEED_MULTIPLIER;

}

