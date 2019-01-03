/*
 * CubeHandler.h
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_CUBEHANDLER_H_
#define SRC_TELEOP_CONTROLMECHANISMS_CUBEHANDLER_H_

// Team302 includes
#include <mechanisms/ICubeHandler.h>
#include <teleop/TeleopControl.h>
#include <subsys/ActiveGrabber.h>
#include <subsys/Grabber.h>
#include <subsys/Lift.h>

#include <mechanisms/CubeToFloor.h>
#include <mechanisms/CubeToSwitch.h>
#include <mechanisms/CubeToScale.h>
#include <mechanisms/CubeHoldPos.h>
#include <mechanisms/CubeManualControl.h>


class CubeHandler
{
	public:
		CubeHandler();
		virtual ~CubeHandler() = default;

	    //-----------------------------------------------------------------------------------
	    // Method:          Periodic
	    // Description:     Run the mechanism
	    // Returns:         void
	    //-----------------------------------------------------------------------------------
		void Periodic();

	    void SetState
		(
				ICubeHandler::CURRENT_CUBEHANDLER_STATE	state
		);

	    void ResetHeight();

	private:
	    TeleopControl*								m_controller;
	    Grabber*									m_grabber;
	    ActiveGrabber*                              m_activeGrabber;
        Lift*                   					m_lift;
	    ICubeHandler::CURRENT_CUBEHANDLER_STATE		m_currentState;

	    const float 								DEAD_BAND = 0.2;
	    bool 										m_dbPassed; // deadband passed
	    bool 										m_safetyToggle;
	    bool 										m_prevBackButton;
	    bool										m_fourBarState; //do we want it up or down
};

#endif /* SRC_TELEOP_CONTROLMECHANISMS_CUBEHANDLER_H_ */
