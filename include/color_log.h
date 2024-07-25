#ifndef COLOR_LOG_H
#define COLOR_LOG_H

#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define LOG_INFO(format, ...) printf(ANSI_COLOR_GREEN "INFO: " format ANSI_COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_WARN(format, ...) fprintf(stdout, ANSI_COLOR_YELLOW "WARN: " format ANSI_COLOR_RESET "\n", ##__VA_ARGS__)
#define LOG_ERROR(format, ...) fprintf(stderr, ANSI_COLOR_RED "ERROR: " format ANSI_COLOR_RESET "\n", ##__VA_ARGS__)

#endif // COLOR_LOG_H