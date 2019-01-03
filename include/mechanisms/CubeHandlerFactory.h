/*
 * CubeHandlerFactory.h
 */

#ifndef SRC_FACTORIES_CUBEHANDLERFACTORY_H_
#define SRC_FACTORIES_CUBEHANDLERFACTORY_H_

#include <mechanisms/ICubeHandler.h>
#include <mechanisms/CubeHandler.h>
#include <mechanisms/CubeHoldPos.h>
#include <mechanisms/CubeManualControl.h>
#include <mechanisms/CubeToFloor.h>
#include <mechanisms/CubeToScale.h>
#include <mechanisms/CubeToSwitch.h>

class CubeHandlerFactory
{
	public:
		static CubeHandlerFactory* GetInstance();
		~CubeHandlerFactory();
		ICubeHandler* GetHandler
		(
		    ICubeHandler::CURRENT_CUBEHANDLER_STATE state
		);

	private:
		CubeHandlerFactory();

	    CubeHandler*					            m_handler;
	    CubeToFloor*					            m_floorHandler;
	    CubeToSwitch*					            m_switchHandler;
	    CubeToScale*					            m_scaleHandler;
	    CubeHoldPos*					            m_holdHandler;
	    CubeManualControl*				            m_manualHandler;

	    ICubeHandler::CURRENT_CUBEHANDLER_STATE		m_currentState;

		static CubeHandlerFactory*		            m_factory;


};

#endif /* SRC_FACTORIES_CUBEHANDLERFACTORY_H_ */
