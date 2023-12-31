#ifndef LOGGING_H
#define LOGGING_H

#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

#include "UtilConstants.h"

namespace Logging {
const std::string keyPrefix = "LOG";

static void logToSmartDashboard(const std::string &key, const std::string &msg,
                                Level level = Level::INFO, Type type = Type::String) {
  if ((int)level < (int)kMinLogLevel)
    return;
  switch (type) {
    case Type::Number:
      frc::SmartDashboard::PutNumber(key, std::stod(msg));
      break;
    default:
      frc::SmartDashboard::PutString(key, msg);
      break;
  }
}

static void logToStdOut(const std::string &key, const std::string &msg,
                        Level level = Level::VERBOSE) {
  if ((int)level < (int)kMinLogLevel)
    return;
  switch (level) {
  case Level::VERBOSE:
    std::cout << "VERBOSE: "
              << "[" << key << "] " << msg << std::endl;
    break;
  case Level::INFO:
    std::cout << "INFO: "
              << "[" << key << "] " << msg << std::endl;
    break;
  case Level::WARNING:
    std::cout << "WARNING: "
              << "[" << key << "] " << msg << std::endl;
    break;
  case Level::ERROR:
    std::cerr << "ERROR: "
              << "[" << key << "] " << msg << std::endl;
    break;
  default:
    std::cout << "LOG: "
              << "[" << key << "] " << msg << std::endl;
    break;
  }
}

} // namespace Logging

#endif