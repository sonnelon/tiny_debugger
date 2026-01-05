#pragma once

#include "logger.h"

typedef enum {
    DBG_FAIL = -1,
    DBG_OK = 0,
    DBG_ERR_MEM_ALLOC = -2,
    DBG_ERR_INVALID_ARG = -3,
    DBG_ERR_FAILED_CREATE_PROCCESS = -4,
    DBG_ERR_CHILD_EXIT = -5,
} dbg_err_t;
