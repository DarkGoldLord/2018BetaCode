/*
 * ActiveGrabber.cpp
 *
 */

#include <subsys/MechanismFactory.h>
#include <vector>

#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/DragonSolenoid.h>
#include <hw/DragonTalon.h>
#include <subsys/IMechanism.h>

#include <subsys/ActiveGrabber.h>

ActiveGrabber::ActiveGrabber
(
        IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
        const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
        const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
        const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
        const DragonAnalogInputVector&      analogInputs,       // <I> - Analog Inputs
        const DragonServoVector&            servos              // <I> - servos
) : m_grabSolenoid( nullptr ),
    m_grabClutchSolenoid( nullptr ),
    m_cubePresent( nullptr ),
    m_wheels( nullptr )
{
    LidarFactory* factory = LidarFactory::GetLidarFactory();
    if ( factory != nullptr )
    {
        m_cubePresent = factory->GetLidar( DragonLidar::FORWARD_GRABBER );
    }

//    printf( " creating active grabber \n" );
    if ( motorControllers.size() > 0 )
    {
        DragonTalon::TALON_TYPE mType= motorControllers[0]->GetType();
        if ( mType == DragonTalon::ACTIVE_INTAKE_WHEELS )
        {
//            printf( "adding intake wheels \n");
            m_wheels = motorControllers[0];
            m_wheels->SetControlMode( DragonTalon::PERCENT );
        }
    }

    for ( unsigned int inx=0; inx<solenoids.size(); ++inx )
    {
//        printf( "==> solenoids [ %d ] = %d \n", inx, solenoids[inx]->GetType() );
        switch ( solenoids[inx]->GetType() )
        {
        case DragonSolenoid::GRABBER_CLUTCH:
            m_grabClutchSolenoid = solenoids[inx];
//            printf( "got clutch \n");
            break;

        case DragonSolenoid::GRABBER_POSITION:
//            printf( "got grab \n");
            m_grabSolenoid = solenoids[inx];
            break;

        default:
            break;
        }
    }
}

ActiveGrabber::~ActiveGrabber()
{
}


IMechanism::MECHANISM_TYPE ActiveGrabber::GetType() const
{
    return IMechanism::ACTIVE_GRABBER;
}

void ActiveGrabber::SpinWheels
(
     double   power
)
{
    if ( m_wheels != nullptr )
    {
         m_wheels->Set( power );
    }
}

void ActiveGrabber::CloseActiveGrabber( bool close )
{
    if ( m_grabClutchSolenoid != nullptr )
    {
        m_grabClutchSolenoid->Set( close );
//        printf("ActiveGrabber closed or opened \n");
    }
}

bool ActiveGrabber::GetCubePresent()
{
	return ( m_cubePresent->GetDistance() < 9.0 );
}


