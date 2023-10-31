#include <subsystems/IntakeSubsystem.h>
#include "moduledrivers/ConnectorX.h"

IntakeSubsystem::IntakeSubsystem(ConnectorX::ConnectorX* subsystem)
    : m_ledSubsystem(subsystem) {}

void IntakeSubsystem::Periodic() {}

void IntakeSubsystem::SimulationPeriodic() {}

void IntakeSubsystem::Out() {
    if (m_ledSubsystem->compareColor(m_ledSubsystem->getCurrentColor(ConnectorX::LedPort::P0), kYellowColor)) {
        m_intakeSpinnyBoy.Set(-ArmConstants::kOuttakeSpeed);
    } else {
        m_intakeSpinnyBoy.Set(ArmConstants::kOuttakeSpeed);
    }
}

void IntakeSubsystem::In() {
    if (m_ledSubsystem->compareColor(m_ledSubsystem->getCurrentColor(ConnectorX::LedPort::P0), kPurpleColor)) {
        m_intakeSpinnyBoy.Set(-ArmConstants::kIntakeSpeed);
    } else {
        m_intakeSpinnyBoy.Set(ArmConstants::kIntakeSpeed);
    }
}

void IntakeSubsystem::Stop() { m_intakeSpinnyBoy.Set(0.0); }