#include "commands/Autos.h"
#include <frc/geometry/Pose2d.h>
#include <pathplanner/lib/path/PathPlannerPath.h>
#include <pathplanner/lib/auto/AutoBuilder.h>

using namespace pathplanner;
using namespace autos;

std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap;

AutoBuilder::configureHolonomic(
    [this]() { return m_drive.GetPose(); }, // Function to supply current robot pose
    [this](frc::Pose2d initPose) { m_drive.ResetOdometry(initPose); }, // Function used to reset odometry at the beginning of auto
    [this]() {return m_drive.getSpee}
    );

frc2::CommandPtr fullAuto = autoBuilder.fullAuto(pathGroup);