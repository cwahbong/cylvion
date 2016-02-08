#include "cylvion/lib.h"
#include "log_int.h"

cyl_error
cyl_lib_init()
{
    return cyl_log_init();
}

void
cyl_lib_free()
{
    cyl_log_free();
}
