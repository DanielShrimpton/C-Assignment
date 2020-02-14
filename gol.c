#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "gol.h"

void read_in_file(FILE *infile, struct universe *u)
{
    u->c = 0, u->r = 0;
    u->curr = 0.0f, u->tot = 0.0f;
    u->c_alive = 0, u->t_alive = 0;
    u->cells = (char **)calloc(1, sizeof(char *));
    for (int i = 0; i < 1; i++)
    {
        u->cells[i] = (char *)calloc(512, sizeof(char));
    }
    int i = 0;
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
        if (size != u->c + 1)
        {
            fprintf(stderr, "gameoflife: Poorly formatted file! Line lengths inconsistent. (%d, %d)\n", size, u->c);
            exit(1);
        }
        for (int k = 0; k < size; k++)
        {
            if (!((u->cells[i][k] == '.') | (u->cells[i][k] == '*') | (u->cells[i][k] == '\n') | (u->cells[i][k] == '\r')))
            {
                fprintf(stderr, "gameoflife: Poorly formatted file! Contains illegal character: %c.\n", u->cells[i][k]);
                exit(1);
            }
            if (u->cells[i][k] == '*')
            {
                u->c_alive++;
                u->t_alive++;
            }
        }
        // u->cells[i][strlen(u->cells[i]) - 1] = '\0';
        u->cells = (char **)realloc(u->cells, (i + 2) * sizeof(char *));
        u->cells[i + 1] = (char *)calloc(size, sizeof(char));
        i++;
    }
    u->r++;
    u->cells[i] = (char *)realloc(u->cells[i], 2 * sizeof(char));
    u->cells[i] = '\0';
    u->curr = u->c * u->r;
    u->tot = u->c * u->r;
}

void write_out_file(FILE *outfile, struct universe *u)
{
    for (int i = 0; i < u->r; i++)
    {
        fputs(u->cells[i], outfile);
    }
    // printf("Written successfully!\n");
}

int is_alive(struct universe *u, int column, int row)
{
    if (u->cells[row - 1][column - 1] == '*')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int will_be_alive(struct universe *u, int column, int row)
{
    int k = 0;
    int count = 0;
    int alive = is_alive(u, column, row);
    int neighbors[8];
    int temp1, temp2;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!(i == 0 && j == 0))
            {
                temp1 = column + i;
                temp2 = row + j;
                if ((temp1 < 1) | (temp1 > u->c))
                {
                    neighbors[k] = 0;
                }
                else if ((temp2 < 1) | (temp2 > u->r))
                {
                    neighbors[k] = 0;
                }
                else
                {
                    neighbors[k] = is_alive(u, temp1, temp2);
                }
                k++;
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        if (count == 4)
        {
            return 0;
        }
        if (neighbors[i] == 1)
        {
            count++;
        }
    }

    if (alive == 1)
    {
        if (count < 2)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (count == 3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int will_be_alive_torus(struct universe *u, int column, int row)
{
    int k = 0;
    int count = 0;
    int alive = is_alive(u, column, row);
    int neighbors[8];
    int temp1, temp2;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (!(i == 0 && j == 0))
            {
                temp1 = column + i;
                temp2 = row + j;
                if (temp1 < 1)
                {
                    temp1 = u->c;
                }
                else if (temp1 > u->c)
                {
                    temp1 = 1;
                }
                if (temp2 < 1)
                {
                    temp2 = u->r;
                }
                else if (temp2 > u->r)
                {
                    temp2 = 1;
                }
                neighbors[k] = is_alive(u, temp1, temp2);
                k++;
            }
        }
    }

    for (int i = 0; i < 8; i++)
    {
        if (count == 4)
        {
            return 0;
        }
        if (neighbors[i] == 1)
        {
            count++;
        }
    }

    if (alive == 1)
    {
        if (count < 2)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (count == 3)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row))
{
    // printf("Evolving\n");
    struct universe n;
    n.c_alive = 0;
    n.r = u->r;
    n.c = u->c;
    (&n)->cells = (char **)calloc(n.r, sizeof(char *));
    for (int i = 0; i < n.r; i++)
    {
        (&n)->cells[i] = (char *)calloc(n.c, sizeof(char));
    }
    int i = 0, j = 0;
    for (i = 0; i < n.r; i++)
    {
        for (j = 0; j < n.c; j++)
        {
            int will = rule(u, j + 1, i + 1);
            char cell[1];
            if (will == 1)
            {
                cell[0] = '*';
                n.c_alive++;
            }
            else
            {
                cell[0] = '.';
            }
            (&n)->cells[i][j] = cell[0];
        }
    }
    u->c_alive = n.c_alive;
    u->t_alive += n.c_alive;
    u->tot += u->curr;
    for (i = 0; i < n.r; i++)
    {
        memcpy(u->cells[i], (&n)->cells[i], u->c + 1);
        u->cells[i][u->c] = '\n';
        free((&n)->cells[i]);
    }
    free((&n)->cells);
}

void print_statistics(struct universe *u)
{
    float curr, total;
    curr = u->c_alive / u->curr;
    total = u->t_alive / u->tot;
    printf("%.3f%% of cells currently alive\n", curr);
    printf("%.3f%% of cells alive on average\n", total);
}