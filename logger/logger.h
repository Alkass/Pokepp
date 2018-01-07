#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

using std::cout;
using std::endl;

typedef enum {
  FATAL = 0,
  ERROR,
  WARN,
  INFO,
  PASS
} LogType;

class Logger {
public:
  int fatal, error, warning, info, pass;
  Logger();
  void log(LogType, const char*, ...);
  ~Logger();
};
#endif
