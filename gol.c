#include <stdio.h>
#include <string.h>
#include "gol.h"

void main()
{
    struct universe *v[24][512];
    FILE *fp;
    fp = fopen("glider.txt", "r");
    read_in_file(fp, v);
    fclose(fp);
}