#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include"gol.h"
// #include "gol.c"
int main(int argc, char *argv[])
{
    char command[10];
    bool stats = false, torus = false;
    struct universe v;
    FILE *fp;
    FILE *op;
    char in_name[100];
    char out[100];
    int gens = 5;

    for (int i = 0; i < argc; i++)
    {
        // printf("%s\n", argv[i]);
        switch (argv[i][0])
        {
        case '-':
            switch (argv[i][1])
            {
            case 'i':
                // strcpy(command, "input");
                strcpy(in_name, argv[i+1]);
                i++;
                break;
            case 'o':
                strcpy(command, "output");
                strcpy(out, argv[i+1]);
                i++;
                break;
            case 'g':
                strcpy(command, "gens");
                gens = strtol(argv[i+1], NULL, 10);
                i++;
                break;
            case 's':
                strcpy(command, "stats");
                stats = true;
                break;
            case 't':
                strcpy(command, "torus");
                torus = true;
                break;
            default:
                printf("Invalid argument!\n");
                exit(1);
            }
        }
    }
    
    // fgets(name, sizeof(name), stdin);
    // char *newline = strchr(name, '\n');
    // if (newline)
    // {
    //     *newline = '\0';
    // }
    fp = fopen(in_name, "r");
    read_in_file(fp, &v);
    
    for (int i = 0; i<gens; i++)
    {
        if (torus) 
        {
            evolve(&v, will_be_alive_torus);
        } else {
            evolve(&v, will_be_alive);
        }
    }
    if (stats)
    {
        print_statistics(&v);
    }
    op = fopen(out, "w");
    write_out_file(op, &v);
    return 0;
}
