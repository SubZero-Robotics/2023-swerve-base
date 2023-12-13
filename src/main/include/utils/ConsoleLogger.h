#include <iostream>

#include "ILogger.h"
#include "UtilConstants.h"

using namespace Logging;

class ConsoleLogger : ILogger {
 public:
  ConsoleLogger() {
    std::cout << "INFO - ConsoleLogger: Console Logger initialized!" << std::endl;
  }

  void logVerbose(std::string key, std::string val) {
    log(Level::VERBOSE, key, val);
  }

  void logInfo(std::string key, std::string val) {
    log(Level::INFO, key, val);
  }

  void logWarning(std::string key, std::string val) {
    log(Level::WARNING, key, val);
  }

  void logError(std::string key, std::string val) {
    log(Level::ERROR, key, val);
  }

  void logFatal(std::string key, std::string val) {
    log(Level::FATAL, key, val);
  }

  void logInfo(std::string key, int val) { return;};
  void logVerbose(std::string key, int val) { return;};
  void logWarning(std::string key, int val) { return;};
  void logError(std::string key, int val) { return;};
  void logFatal(std::string key, int val) { return;};

  void logInfo(std::string key, double val) { return;};
  void logVerbose(std::string key, double val) { return;};
  void logWarning(std::string key, double val) { return;};
  void logError(std::string key, double val) { return;};
  void logFatal(std::string key, double val) { return;};

  private:

  void log(Level level, std::string key, std::string val) {
    if ((int)level < (int)kMinLogLevel) return;
    std::cout << levelToString(level) << " - " << key << ": " << val << std::endl;
  }
};