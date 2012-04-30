/**
 * log.h
 * Copyright (C) 2012 Jan Viktorin
 */

#ifndef LOG_H
#define LOG_H

#define LOG_CGP  0x01

#ifndef LOG_MASK
#define LOG_MASK 0
#endif

#include <stdarg.h>
#define log_enabled(level) (LOG_MASK & (level))
#define log(level, fmt, ...) if(log_enabled(level)) {x__log(level, fmt, __VA_ARGS);}
#define log_call(level) if(log_enabled(level)) {x__log(level, \
		"%s#%s:%d", __FILE__, __func__, __LINE__);}

const char *x__level_as_str(int l)
{
	switch(l) {
	case LOG_CGP:
		return "CGP";
	default:
		return "???";
	}
}

static inline
x__log(int level, const char *fmt, ...)
{
	fprintf(stderr, "[%s] ", x__level_as_str(level));

	va_list args;
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fprintf(stderr, "\n");
}

#endif

