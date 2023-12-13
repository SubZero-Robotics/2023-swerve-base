#ifndef ILOGGER_H
#define ILOGGER_H

#include <string.h>

class ILogger {
 public:
  // string
  virtual void logVerbose(std::string key, std::string val) = 0;
  virtual void logInfo(std::string key, std::string val) = 0;
  virtual void logWarning(std::string key, std::string val) = 0;
  virtual void logError(std::string key, std::string val) = 0;
  virtual void logFatal(std::string key, std::string val) = 0;

  // int
  virtual void logVerbose(std::string key, int val) = 0;
  virtual void logInfo(std::string key, int val) = 0;
  virtual void logWarning(std::string key, int val) = 0;
  virtual void logError(std::string key, int val) = 0;
  virtual void logFatal(std::string key, int val) = 0;

  // double
  virtual void logVerbose(std::string key, double val) = 0;
  virtual void logInfo(std::string key, double val) = 0;
  virtual void logWarning(std::string key, double val) = 0;
  virtual void logError(std::string key, double val) = 0;
  virtual void logFatal(std::string key, double val) = 0;

 protected:
  std::string levelToString(Level level) {
    switch (level) {
        case Level::VERBOSE:
            return "VERBOSE";
        case Level::INFO:
            return "INFO";
        case Level::WARNING:
            return "WARNING";
        case Level::ERROR:
            return "ERROR";
        case Level::FATAL:
            return "FATAL";
    };
  }
};

#endif