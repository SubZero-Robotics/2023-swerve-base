#pragma once

#include <rev/CANSparkMax.h>
#include <frc2/command/CommandPtr.h>
#include <frc2/command/SubsystemBase.h>
#include "moduledrivers/ConnectorX.h"

#include "constants.h"

using namespace CANSparkMaxConstants;

static const ConnectorX::Commands::CommandColor kYellowColor = {
    .red = 0xff,
    .green = 0xff,
    .blue = 0x00
};
static const ConnectorX::Commands::CommandColor kPurpleColor = {
    .red = 110,
    .green = 10,
    .blue = 250
};


class IntakeSubsystem : public frc2::SubsystemBase {
   public:
    IntakeSubsystem(ConnectorX::ConnectorX* subsystem);

    /**
     * Will be called periodically whenever the CommandScheduler runs.
     */
    void Periodic() override;

    /**
     * Will be called periodically whenever the CommandScheduler runs during
     * simulation.
     */
    void SimulationPeriodic() override;

    void Out();
    void In();
    void Stop();

   private:
    // Components (e.g. motor controllers and sensors) should generally be
    // declared private and exposed only through public methods.
    ConnectorX::ConnectorX* m_ledSubsystem;
    rev::CANSparkMax m_intakeSpinnyBoy;
};