#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char *format, ...)

#ifdef _GNUC_
#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif

#endif

