#include "commands/Autos.h"
#include <frc/geometry/Pose2d.h>
#include <pathplanner/lib/path/PathPlannerPath.h>
#include <pathplanner/lib/auto/AutoBuilder.h>

using namespace pathplanner;
using namespace autos;

std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap;