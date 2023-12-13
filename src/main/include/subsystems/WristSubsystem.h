#pragma once

#include "Constants.h"
#include "rev/CANSparkMax.h"
#include "subsystems/BaseSingleAxisSubsystem.h"
#include "utils/ConsoleLogger.h"

class WristSubsystem
    : public BaseSingleAxisSubsystem<rev::CANSparkMax,
                                     rev::SparkMaxAbsoluteEncoder,
                                     units::degree, units::degree_t> {
   public:
    WristSubsystem()
        : BaseSingleAxisSubsystem(m_config, m_wristMotor, m_encoder, &min,
                                  nullptr, "WRIST", "\033[92;40;4m") {
        _config = m_config;
        _controller = m_config.pid;
        _controller.SetTolerance(10, 10);
        m_encoder.SetPositionConversionFactor(1);
    }

    // Wrist has zero offset set in SparkMax
    void ResetEncoder() override {
        if (_log)
            m_consoleLogger.logInfo(_prefix, "RESET POSITION");
        // m_encoder.SetZeroOffset(0);
    }

    double GetCurrentPosition() override {
        auto position = m_encoder.GetPosition() * _config.distancePerRevolution;

        if (position >= 350) position = 0;

        Logging::logToSmartDashboard("WristPosition",
                                     std::to_string(position) + " deg",
                                     Logging::Level::INFO, Logging::Type::Number);

        if (_log)
            m_consoleLogger.logInfo(_prefix, std::to_string(position) + "/" +
                                     std::to_string(_config.maxDistance) +
                                     " deg");

        return position;
    }

    void RunMotorExternal(double speed) override {
        // TODO: constant
        if (abs(speed) <= 0.05) {
            if (_isMovingToPosition)
                return;  // Don't set the motor and overwrite a potential
                         // automated movement

            if (_config.type == AxisType::Rotational)
                RunMotorSpeed(-0.005);
            else
                _motor.Set(0);
            return;
        }

        // Overwrite current automated position with joystick input
        if (_isMovingToPosition) {
            StopMovement();
        }

        RunMotorSpeed(speed);
    }

    void UpdateMovement() override {
        if (_isMovingToPosition) {
            if (_log)
                m_consoleLogger.logInfo(_prefix, "Target Position: " + std::to_string(_targetPosition) +
                        std::string(_config.type == AxisType::Linear ? " in"
                                                                     : " deg"));

            // TODO: extract multipliers to constants and pass through the
            // config
            auto res =
                _controller.Calculate(GetCurrentPosition(), _targetPosition);
            auto clampedRes = std::clamp(res, -1.0, 1.0) * 0.66;
            if (_log)
                m_consoleLogger.logInfo(_prefix, "Clamped Res: " + std::to_string(clampedRes));
            Logging::logToSmartDashboard(_prefix + " TargetPos",
                                         std::to_string(_targetPosition),
                                         Logging::Level::INFO, Logging::Type::Number);

            if (_controller.AtSetpoint()) {
                m_consoleLogger.logInfo(_prefix, "REACHED GOAL");
                StopMovement();
                return;
            }

            RunMotorSpeed(clampedRes);
        }
    }

   private:
    ConsoleLogger m_consoleLogger;
    rev::CANSparkMax m_wristMotor{CANSparkMaxConstants::kWristRotationMotorID,
                                  rev::CANSparkMax::MotorType::kBrushless};

    rev::SparkMaxAbsoluteEncoder m_encoder = m_wristMotor.GetAbsoluteEncoder(
        rev::SparkMaxAbsoluteEncoder::Type::kDutyCycle);

    SingleAxisConfig m_config = {
        .type = BaseSingleAxisSubsystem::AxisType::Rotational,
        .pid = frc::PIDController(ArmConstants::kWristSetP,
                                   ArmConstants::kWristSetI,
                                   ArmConstants::kWristSetD),
        .minDistance = 0,
        .maxDistance = ArmConstants::kWristDegreeLimit,
        .distancePerRevolution = 360.0,
        .stepSize = ArmConstants::kWristStepSize,
        .motorMultiplier = 1.0,
        .minLimitSwitchPort = ArmConstants::kWristLimitSwitchPort,
        .maxLimitSwitchPort = BaseSingleAxisSubsystem::UNUSED_DIO_PORT,
        .defaultMovementSpeed = -ArmConstants::kWristHomingSpeed};

    frc::DigitalInput min{ArmConstants::kWristLimitSwitchPort};
};