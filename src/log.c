#include <__stdarg_va_list.h>
#include <cstdarg>
#include <stdio.h>
#include <unistd.h>

#include "log.h"

static int LOG_FILE = STDERR_FILENO;

void log_error(const char *fmt, ...) {
  log_message(LOG_ERROR, fmt, ...);
}

void set_log_file(int file) { LOG_FILE = file; }

void log_message(int level, const char *fmt, ...) {
  va_list args;
  va_stat(args, fmt);
  vfprintf(LOG_FILE, fmt, );
}
