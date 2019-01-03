/*
 * CubeManualControl.h
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_CUBEMANUALCONTROL_H_
#define SRC_TELEOP_CONTROLMECHANISMS_CUBEMANUALCONTROL_H_


// Team302 includes
#include <mechanisms/ICubeHandler.h>
#include <teleop/TeleopControl.h>
#include <subsys/Grabber.h>
#include <subsys/Lift.h>
#include <mechanisms/CubeHandler.h>

class CubeManualControl  : public ICubeHandler
{
	public:
		CubeManualControl();
		virtual ~CubeManualControl() = default;

		//-----------------------------------------------------------------------------------
		// Method:          Periodic
		// Description:     Run the mechanism
	    // Returns:         ICubeHandler::CURRENT_CUBEHANDLER_STATE		next state to run
		//-----------------------------------------------------------------------------------
		ICubeHandler::CURRENT_CUBEHANDLER_STATE Periodic() override;

	private:
		TeleopControl*			m_controller;
		Lift*					m_lift;

};

#endif /* SRC_TELEOP_CONTROLMECHANISMS_CUBEMANUALCONTROL_H_ */
