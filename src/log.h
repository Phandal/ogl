#ifndef LOG_H

#define LOG_H
void log_set_file(int file);

void log_error(const char *fmt, ...);
void log_warn(const char *fmt, ...);
void log_info(const char *fmt, ...);
void log_debug(const char *fmt, ...);

#endif // LOG_H
