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
    char base[256];
    wvatha_err result = get_base(path, base);
    if (result != 0) {
        printf("error on get_working_dir()\n");
        exit(result);
    }
    char tbase[256];

    result = get_base(base, tbase);
    if (result != 0) {
        printf("error on get_working_dir()\n");
        exit(result);
    }
    printf("get_base(): base path is %s\n", base);
    printf("get_base(): base path is %s\n", tbase);

    return 0;
}

#elif OSX
#include <unistd.h>

#else
#include <unistd.h>
#endif 