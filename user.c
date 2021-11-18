#include "user.h"

int userArgument(int argc, char *argv[], char *path)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            printf("Compression file: %s\n", argv[i+1]);
            return 1;
        }

        if (strcmp(argv[i], "-d") == 0)
        {
            printf("Decompression file: %s\n", argv[i+1]);
            return 2;
        }

        if (strcmp(argv[i], "-h") == 0)
        {
            printf("Help: %s\n", argv[i]);
            return 2;
        }
        
    }
    
    return 0;   //Quit program
}