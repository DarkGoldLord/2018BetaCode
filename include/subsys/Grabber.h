/*
 * Grabber.h
 *
 */

#ifndef SRC_SUBSYS_MECHANISMS_GRABBER_H_
#define SRC_SUBSYS_MECHANISMS_GRABBER_H_

#include <subsys/MechanismFactory.h>
#include <vector>

#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/DragonSolenoid.h>
#include <hw/DragonTalon.h>
#include <subsys/IMechanism.h>


class Grabber  : public IMechanism
{
    public:

        Grabber() = delete;
        Grabber
        (
                IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
                const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
                const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
                const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
                const DragonAnalogInputVector&         analogInputs,       // <I> - Analog Inputs
                const DragonServoVector&            servos              // <I> - servos
        );
        virtual ~Grabber();

        IMechanism::MECHANISM_TYPE GetType() const override;

        void SpinGrabber
        (
            bool            close
        );

        void CloseGrabber
        (
            bool            close
        );

        bool GetCubePresent();

    private:
        DragonSolenoid*         m_grabSolenoid;
        DragonSolenoid*         m_grabClutchSolenoid;
        DragonDigitalInput* 	m_cubePresent;

};

#endif /* SRC_SUBSYS_MECHANISMS_GRABBER_H_ */
