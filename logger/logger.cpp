#include <stdio.h>
#include <stdio.h>   // vprintf
#include <stdarg.h>  // va_list, va_start, va_end
#include "logger.h"

Logger::Logger() {
  this->fatal   = 0;
  this->error   = 0;
  this->warning = 0;
  this->info    = 0;
  this->pass    = 0;
}

void Logger::log(LogType log_type, const char* format, ...) {
  switch (log_type) {
    case LogType::FATAL:
      this->fatal++;
      printf("  \033[1;31mFATAL\033[0;00m: ");
      break;
    case LogType::ERROR:
      this->error++;
      printf("  \033[0;31mERROR\033[0;00m: ");
      break;
    case LogType::WARN:
      this->warning++;
      printf("  \033[1;33mWARN\033[0;00m:  ");
      break;
    case LogType::INFO:
      this->info++;
      printf("  \033[0;34mINFO\033[0;00m:  ");
      break;
    case LogType::PASS:
      this->pass++;
      printf("  \033[0;32mPASS\033[0;00m:  ");
      break;
  }
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n");
}

Logger::~Logger() {
  cout <<
    "FATAL " << this->fatal    << "  " <<
    "ERROR " << this->error    << "  " <<
    "WARN "  << this->warning  << "  " <<
    "INFO "  << this->info     << "  " <<
    "PASS "  << this->pass     << "  " <<
    endl;
}
