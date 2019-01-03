/*
 * Climber.h
 *
 */

#ifndef SRC_SUBSYS_MECHANISMS_CLIMBER_H_
#define SRC_SUBSYS_MECHANISMS_CLIMBER_H_

#include <subsys/MechanismFactory.h>
#include <subsys/IMechanism.h>
#include <vector>

#include <hw/DragonAnalogInput.h>
#include <hw/DragonDigitalInput.h>
#include <hw/DragonServo.h>
#include <hw/DragonSolenoid.h>
#include <hw/DragonTalon.h>


class Climber  : public IMechanism
{
    public:
        Climber() = delete;
        Climber
        (
                IMechanism::MECHANISM_TYPE          type,               // <I> - manipulator Type
                const DragonTalonVector&            motorControllers,   // <I> - Motor Controllers
                const DragonSolenoidVector&         solenoids,          // <I> - Solenoids
                const DragonDigitalInputVector&     digitalInputs,      // <I> - Digital Inputs
                const DragonAnalogInputVector&         analogInputs,       // <I> - Analog Inputs
                const DragonServoVector&            servos              // <I> - servos
        );
        virtual ~Climber();

        IMechanism::MECHANISM_TYPE GetType() const override;

        void RunWinch();
        void StopWinch();
        void ReverseWinch();

        void SaveHoldTarget();
        void HoldPosition();

        bool IsClimbing();

    private:
        DragonTalon*            m_climbMotor;
        float                   m_holdTarget;

        const float             m_climbSpeed = 1.0;
        const float             m_stopSpeed  = 0.0;

        const float             m_hold_kP = 20.0;
        const float             m_hold_kI = 0.0;
        const float             m_hold_kD = 0.0;
        const float             m_hold_kF = 0.0;
};

#endif /* SRC_SUBSYS_MECHANISMS_CLIMBER_H_ */
