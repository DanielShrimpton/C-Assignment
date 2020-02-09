#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

void main()
{
    struct universe v;
    FILE *fp;
    fp = fopen("glider.txt", "r");
    read_in_file(fp, &v);
    fclose(fp);
    int r = 0, c = 0;
    // Why doesn't this one work?? 
    // while (v.cells[0][c] != '\n') 
    while ((v.cells[0][c] == '.') | (v.cells[0][c] == '*'))
    {
        c++;
    }
    while ((v.cells[r] != NULL) && (*v.cells[r] != '\0'))
    {
        r++;
    }
}