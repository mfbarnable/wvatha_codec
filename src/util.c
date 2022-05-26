#include "util.h"
#include <string.h>

#ifdef WIN32
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
    const unsigned long maxDir = 1024;
    char currentDir[maxDir];
    GetCurrentDirectory(maxDir, currentDir);
    strcpy(wd, currentDir);
    return 0;
}

wvatha_err get_base(char *path, char *base_path) {
    const char delim = '\\';
    int len = strlen(path);
    for (int i = len - 1; i >= 0; i--) {
        if (delim == path[i]) {
            memset(base_path, 0, sizeof(base_path));
            strncpy(base_path, path, i + 1);
            base_path[i + 1] = '\0';
            return 0;
        } 
    }
    return err_char_nf;
}

#elif OSX
#include <unistd.h>

#else
#include <unistd.h>
#endif 