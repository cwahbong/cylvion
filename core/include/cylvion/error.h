#ifndef CYLVION_ERROR_H
#define CYLVION_ERROR_H

typedef enum {
    CYL_OK = 0,
    CYL_ERR = -1,
    CYL_BAD_PARAM = -2,
    CYL_BAD_STATE = -3,
} cyl_error;

typedef enum {
    CYL_WIN = 0,
    CYL_LOSE = -1,
    CYL_UNKNOWN = -2,
} cyl_result;

#endif /* CYLVION_ERROR_H */
