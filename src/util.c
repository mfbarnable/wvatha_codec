#include "util.h"
#include <string.h>
#define NULL_TERM '\0'
#ifdef WIN32
#define WINDOWS_PATH_DELIM '\\'
#define MAX_PATH_LENGTH 260 
#define UNROLL_INDEX(a) (a - 1)
#include <windows.h>

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
int GetLastErrorAsString()
{
    //Get the error message ID, if any.
    DWORD errorMessageID = GetLastError();
    if(errorMessageID == 0) {
        return -1; //No error message has been recorded
    }
    
    LPSTR messageBuffer = NULL;

    //Ask Win32 to give us the string version of that message ID.
    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    //Copy the error message into a std::string.
    printf("Error message is %s\n", messageBuffer);
    
    //Free the Win32's string's buffer.
    LocalFree(messageBuffer);
            
    return 0;
}

wvatha_err get_working_dir(char wd[]) {
    if (NULL == wd) {
        return err_empty_buffer;
    }
    char currentDir[MAX_PATH_LENGTH];
    GetCurrentDirectory(MAX_PATH_LENGTH, currentDir);
    strcpy(wd, currentDir);
    return 0;
}

// Caller free
char *get_base(char *path) {
    int len = strlen(path);
    for (int i = UNROLL_INDEX(len); i >= 0; i--) {
        if (WINDOWS_PATH_DELIM == path[i]) {
            char *base_path = malloc(i);
            memset(base_path, 0, i);
            strncpy(base_path, path, i);
            base_path[i] = NULL_TERM;
            return base_path;
        } 
    }
    return NULL;
}

#elif OSX
#include <unistd.h>

#else
#include <unistd.h>
#endif 