#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gol.h"

void free_cells(struct universe *v);

void main()
{
    struct universe v;
    FILE *fp;
    fp = fopen("glider.txt", "r");
    read_in_file(fp, &v);
    fclose(fp);
    v.r = 0;
    v.c = 0;
    // while (v.cells[0][v.c] != '\n')
    while ((v.cells[0][v.c] == '.') | (v.cells[0][v.c] == '*'))
    {
        v.c++;        
    }
    while ((v.cells[v.r] != NULL) && (*v.cells[v.r] != '\0'))
    {
        v.r++;
    }
    printf("Rows: %d, Columns: %d\n", v.r, v.c);

    FILE *out_file_pointer;
    out_file_pointer = fopen("gilder-out.txt", "w");
    write_out_file(out_file_pointer, &v);
    fclose(out_file_pointer);

    free_cells(&v);

    exit(0);
}

void free_cells(struct universe *v)
{
    for (int i = 0; i < v->r; i++)
    {
        free(v->cells[i]);
        v->cells[i] = NULL; // Best practice
    }
    free(v->cells);
    v->cells = NULL;
    v->c = 0;
    v->r = 0;
    printf("Freed memory!\n");
}

void read_in_file(FILE *infile, struct universe *u)
{
    u->cells = (char **)calloc(1, sizeof(char *));
    for (int i = 0; i < 1; i++)
    {
        u->cells[i] = (char *)calloc(512, sizeof(char));
    }
    int i = 0, j = 0;
    int size;
    bool first = true;
    while (fgets(u->cells[i], 512, infile))
    {
        u->r = i;
        size = strlen(u->cells[i]);
        if (first)
        {
            u->c = size - 1;
            u->cells[i] = (char *)realloc(u->cells[i], size * sizeof(char));
            first = false;
        }
        if (size != u->c + 1) {
            printf("Poorly formatted file!\n");
            free_cells(u);
            exit(1);
        }
        for (int k=0; k<size; k++) {
            if (!((u->cells[i][k] == '.') | (u->cells[i][k] == '*') | (u->cells[i][k] == '\n'))) {
                printf("%c\n", u->cells[i][k]);
                printf("Poorly formatted file!\n");
                free_cells(u);
                exit(1);
            }
        }
        // u->cells[i][strlen(u->cells[i]) - 1] = '\0';
        u->cells = (char **)realloc(u->cells, (i + 2) * sizeof(char *));
        u->cells[i + 1] = (char *)calloc(size, sizeof(char));
        i++;
    }

    u->cells[i] = (char *)realloc(u->cells[i], 2 * sizeof(char));
    u->cells[i] = '\0';
}

void write_out_file(FILE *outfile, struct universe *u)
{
    printf("Writing to file!\n");
    for (int i =0; i<u->r; i++) {
        fputs(u->cells[i], outfile);
    }
}

int is_alive(struct universe *u, int column, int row)
{
    if (u->cells[row-1][column-1] == '*')
    {
        return 1;
    } else {
        return 0;
    }
}