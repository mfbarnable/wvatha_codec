#ifndef _UTIL_H
#define _UTIL_H
#include "err_type.h"


wvatha_err get_working_dir(char wd[]);
wvatha_err get_base(char *path, char *base_path);

#endif // _UTIL_H