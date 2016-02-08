#include <stdarg.h>
#include <stdio.h>

#include "cylvion/log.h"
#include "cylvion/error.h"

#include "log_int.h"

static FILE * fp = NULL;

static FILE *
cyl_log_file()
{
    if (fp == NULL) {
        fp = fopen("cylvioncore.log", "a");
    }
    return fp;
}

cyl_error
cyl_log_init()
{
    if (cyl_log_file() == NULL) {
        return CYL_ERR;
    }
}

void
cyl_log_free()
{
    if (fp != NULL) {
        fclose(fp);
    }
}

static void
cyl_log_print(const char * level, const char * fmt, va_list vl)
{
    FILE * fp = cyl_log_file();
    if (fp == NULL) {
        return;
    }
    fprintf(fp, "[%s] ", level);
    vfprintf(fp, fmt, vl);
    fprintf(fp, "\n");
}

#define CYL_LOG_VA_PRINT(level, fmt) \
    do { \
        va_list vl; \
        va_start(vl, fmt); \
        cyl_log_print(level, fmt, vl); \
        va_end(vl); \
    } while(0)

void
cyl_log_error(const char * fmt, ...)
{
    CYL_LOG_VA_PRINT("E", fmt);
}

void
cyl_log_warn(const char * fmt, ...)
{
    CYL_LOG_VA_PRINT("W", fmt);
}

void
cyl_log_info(const char * fmt, ...)
{
    CYL_LOG_VA_PRINT("I", fmt);
}

void
cyl_log_debug(const char * fmt, ...)
{
    CYL_LOG_VA_PRINT("D", fmt);
}
