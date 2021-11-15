#include "user.h"

int userArgument(int argc, char *argv[], char *path)
{
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-c"))
        {
            printf("Compression: %s\n", argv[i]);
            printf("Path: %s\n", argv[i+1]);
            
        }
        
    }
    
    return 0;
}