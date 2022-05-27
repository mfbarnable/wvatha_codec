#include "util_test.h"
#include "util.h"
#ifdef WIN32
#include <windows.h>

wvatha_err get_working_dir_test() {
    char temp[2048];
    wvatha_err result = get_working_dir(temp);
    if (result != 0) {
        printf("error on get_working_dir()\n");
        exit(result);
    }
    printf("get_working_dir(): current directory is %s\n", temp);
    return 0;
}

wvatha_err get_base_path_test() {
    char *path = "src\\main\\jans.c";
    char *base = get_base(path);
    if (base == NULL) {
        printf("error on get_working_dir()\n");
        exit(-1);
    }
    char *second_base = get_base(base);
    if (second_base == NULL) {
        printf("error on get_working_dir()\n");
        exit(-1);
    }
    printf("get_base(): base path is %s\n", base);
    printf("get_base(): base path is %s\n", second_base);
    free(base); base = 0;
    free(second_base); second_base = 0;
    return 0;
}

#elif OSX
#include <unistd.h>

#else
#include <unistd.h>
#endif 