/*
 * ActiveGrabber.h
 *
 */

#ifndef SRC_SUBSYS_MECHANISMS_ActiveGrabber_H_
#define SRC_SUBSYS_MECHANISMS_ActiveGrabber_H_

#include <subsys/MechanismFactory.h>
#include <hw/LidarFactory.h>
#include <vector>
#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/DragonSolenoid.h>
#include <hw/DragonTalon.h>
#include <hw/DragonLidar.h>
#include <subsys/IMechanism.h>


class ActiveGrabber  : public IMechanism
{
    public:

        ActiveGrabber() = delete;
        ActiveGrabber
        (
                IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
                const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
                const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
                const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
                const DragonAnalogInputVector&      analogInputs,       // <I> - Analog Inputs
                const DragonServoVector&            servos              // <I> - servos
        );
        virtual ~ActiveGrabber();

        IMechanism::MECHANISM_TYPE GetType() const override;

        void SpinWheels
        (
             double   power
        );

        void CloseActiveGrabber
        (
            bool            close
        );

        bool GetCubePresent();

    private:
        DragonSolenoid*         m_grabSolenoid;
        DragonSolenoid*         m_grabClutchSolenoid;
        DragonLidar*     m_cubePresent;
        DragonTalon*            m_wheels;

};

#endif /* SRC_SUBSYS_MECHANISMS_ActiveGrabber_H_ */
