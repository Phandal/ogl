#include <stdarg.h>
#include <stdio.h>

#include "log.h"

static FILE *LOG_FILE = NULL;

enum {
  LOG_ERROR,
  LOG_WARN,
  LOG_INFO,
  LOG_DEBUG,
};

void set_log_file(FILE *file) { LOG_FILE = file; }

void log_message(int level, const char *fmt, va_list args) {
  if (LOG_FILE == NULL) {
    set_log_file(stderr);
  }

  switch (level) {
  case LOG_ERROR:
    fprintf(LOG_FILE, "[ERROR]: ");
    break;
  case LOG_WARN:
    fprintf(LOG_FILE, "[WARN]: ");
    break;
  case LOG_INFO:
    fprintf(LOG_FILE, "[INFO]: ");
    break;
  default:
    fprintf(LOG_FILE, "[DEBUG]: ");
    break;
  }

  vfprintf(LOG_FILE, fmt, args);
  fprintf(LOG_FILE, "\n");
}

void log_error(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log_message(LOG_ERROR, fmt, args);
  va_end(args);
}

void log_warn(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log_message(LOG_WARN, fmt, args);
  va_end(args);
}

void log_info(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log_message(LOG_INFO, fmt, args);
  va_end(args);
}

void log_debug(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  log_message(LOG_DEBUG, fmt, args);
  va_end(args);
}
