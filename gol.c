#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

void free_cells(int r, struct universe *v);

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
    printf("Rows: %d, Columns: %d\n", r, c);

    free_cells(r, &v);

    exit(0);
}

void free_cells(int r, struct universe *v)
{
    for (int i = 0; i < r; i++)
    {
        free(v->cells[i]);
        v->cells[i] = NULL; // Best practice
    }
    free(v->cells);
    v->cells = NULL;
    printf("Freed memory!\n");
}