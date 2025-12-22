#include "utils.h"
#include "globals.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <libcd.h>

char *FileRead(char *filename, u_long *length)
{
    CdlFILE filepos;
    int numsectors;
    char *buffer;

    buffer = NULL;

    if (CdSearchFile(&filepos, filename) == NULL)
    {
        printf("%s file not found in the CD.\n", filename);
    }
    else
    {
        printf("Found %s in the CD.\n", filename);
        numsectors = (filepos.size + 2047) / 2048;
        buffer = (char*) malloc(2048 * numsectors);

        if(!buffer)
        {
            printf("Error allocating %d sectors!\n", numsectors);
        }

        CdControl(CdlSetloc, (u_char*) &filepos.pos, 0);
        CdRead(numsectors, (u_long*) buffer, CdlModeSpeed);
        CdReadSync(0, 0);
    }

    *length = filepos.size;

    return buffer;
}
