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

void read_in_file(FILE *infile, struct universe *u)
{
    u->cells = (char **)calloc(1, sizeof(char *));
    for (int i = 0; i < 1; i++)
    {
        u->cells[i] = (char *)calloc(512, sizeof(char));
    }
    // arr[0] = (char*)calloc(512, sizeof(char));
    int i = 0, j = 0;
    int size;
    bool first = true;
    while (fgets(u->cells[i], 512, infile))
    {
        size = strlen(u->cells[i]);
        if (first)
        {
            u->cells[i] = (char *)realloc(u->cells[i], size * sizeof(char));
            first = false;
        }
        u->cells[i][strlen(u->cells[i]) - 1] = '\0';
        u->cells = (char **)realloc(u->cells, (i + 2) * sizeof(char *));
        u->cells[i + 1] = (char *)calloc(size, sizeof(char));
        i++;
    }

    u->cells[i] = (char *)realloc(u->cells[i], 2 * sizeof(char));
    u->cells[i] = '\0';

    // for (j = 0; j < i; j++)
    // {
    //     printf("%d. %s\n", j, u->cells[j]);
    // }
}

void write_out_file(FILE *outfile, struct universe *u)
{
    
}