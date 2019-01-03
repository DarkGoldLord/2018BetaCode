/*
 * LEDHandler.h
 *
 *  Created on: Mar 27, 2018
 *      Author: Austin
 */

#ifndef SRC_TELEOP_CONTROLMECHANISMS_LEDHANDLER_H_
#define SRC_TELEOP_CONTROLMECHANISMS_LEDHANDLER_H_

// teleop stuff
#include <teleop/TeleopControl.h>
//Interface
#include <subsys/IMechanism.h>
//Factories
#include <subsys/MechanismFactory.h>
#include <hw/LEDFactory.h>
#include <hw/LidarFactory.h>
//Stuff we need
#include <hw/TrueColors.h>
#include <subsys/ActiveGrabber.h>
#include <subsys/Grabber.h>
#include <subsys/Lift.h>
#include <subsys/Climber.h>
#include <hw/DragonLidar.h>

class LEDHandler {
public:
	LEDHandler();
	virtual ~LEDHandler() = default;

    //-----------------------------------------------------------------------------------
    // Method:          Periodic
    // Description:     Run the mechanism
    // Returns:         void
    //-----------------------------------------------------------------------------------
	void TeleopLED();
	void AutonLED();
	void DisabledLED();

private:
	bool				m_ran;

	// colorz
	//TrueColors* m_leds;
	// Mechanismz
	ActiveGrabber* 		m_activeGrabber;
	Grabber* 			m_grabber;
	Lift* 				m_lift;
	Climber*			m_climber;
	// Controller
	TeleopControl*		m_controller;

	//thos lidars (just one of them right now)
	DragonLidar* m_downLidar;

};

#endif /* SRC_TELEOP_CONTROLMECHANISMS_LEDHANDLER_H_ */
