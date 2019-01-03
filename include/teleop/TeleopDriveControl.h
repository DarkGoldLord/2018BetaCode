/*
 * TeleopDriveControl.h
 *
 */

#ifndef SRC_TELEOP_DRIVE_TELEOPDRIVECONTROL_H_
#define SRC_TELEOP_DRIVE_TELEOPDRIVECONTROL_H_

#include <teleop/IDrive.h>

#include <teleop/ArcadeDrive.h>
#include <teleop/TankDrive.h>
#include <teleop/TeleopDrive.h>

class TeleopDriveControl : public IDrive
{
    public:
        TeleopDriveControl();
        virtual ~TeleopDriveControl();

        void Drive() override;
        const char* GetIdentifier() const override;


    private:
        int                 m_loopCount;
        int                 m_currentDriveMode;
        IDrive*             m_driveModes[ 3 ];

};

#endif /* SRC_TELEOP_DRIVE_TELEOPDRIVECONTROL_H_ */
