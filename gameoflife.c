#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "gol.h"

int main(int argc, char *argv[])
{
    bool in = false, out_ = false, stats = false, torus = false, gens_ = false;
    struct universe v;
    FILE *fp;
    FILE *op;
    char in_name[100];
    char out[100];
    int gens = 5;

    for (int i = 1; i < argc; i++)
    {
        switch (argv[i][0])
        {
        case '-':
            switch (argv[i][1])
            {
            case 'i':
            if (!in)
            {
                strcpy(in_name, argv[i + 1]);
                in = true;
                i++;
                break;
            }
            else 
            {
                char temp[100];
                strcpy(temp, argv[i + 1]);
                if (strcmp(in_name, temp) != 0) 
                {
                    fprintf(stderr, "gameoflife: multiple duplicate flags: %s.\n", argv[i]);
                    exit(1);
                }
                i++;
                break;
            }
                
            case 'o':
                if (!out_)
                {
                    strcpy(out, argv[i + 1]);
                    out_ = true;
                    i++;
                    break;
                }
                else
                {
                    char temp[100];
                    strcpy(temp, argv[i + 1]);
                    if (strcmp(out, temp) != 0)
                    {
                        fprintf(stderr, "gameoflife: multiple duplicate flags: %s.\n", argv[i]);
                        exit(1);
                    }
                    i++;
                    break;
                }

            case 'g':
                if (!gens_)
                {
                    gens_ = true;
                    gens = strtol(argv[i + 1], NULL, 10);
                    if (gens < 1)
                    {
                        fprintf(stderr, "gameoflife: please enter a valid, positive integer for number of generations\n");
                        exit(1);
                    }
                    i++;
                    break;
                }
                else
                {
                    int temp;
                    temp = strtol(argv[i + 1], NULL, 10);
                    if (!(temp == gens))
                    {
                        fprintf(stderr, "gameoflife: multiple duplicate flags: %s.\n", argv[i]);
                        exit(1);
                    }
                    i++;
                    break;
                }

            case 's':
                if (!stats)
                {
                    stats = true;
                    break;
                }
                else
                {
                    fprintf(stderr, "gameoflife: multiple duplicate flags: %s.\n", argv[i]);
                    exit(1);
                }

            case 't':
                if (!torus)
                {
                    torus = true;
                    break;
                }
                else
                {
                    fprintf(stderr, "gameoflife: multiple duplicate flags: %s.\n", argv[i]);
                    exit(1);
                }

            default:
                fprintf(stderr, "gameoflife: option %s is unknown\n", argv[i]);
                exit(1);
            }
            break;
        default:
            fprintf(stderr, "gameoflife: option %s is unknown\n", argv[i]);
            exit(1);
        }
    }

    // fgets(name, sizeof(name), stdin);
    // char *newline = strchr(name, '\n');
    // if (newline)
    // {
    //     *newline = '\0';
    // }
    if (in)
    {
        if (access(in_name, F_OK) != -1)
        {
            fp = fopen(in_name, "r");
            read_in_file(fp, &v);
        }
        else
        {
            fprintf(stderr, "gameoflife: the file '%s' does not exist\n", in_name);
            exit(1);
        }
    }
    else
    {
        read_in_file(stdin, &v);
    }

    for (int i = 0; i < gens; i++)
    {
        if (torus)
        {
            evolve(&v, will_be_alive_torus);
        }
        else
        {
            evolve(&v, will_be_alive);
        }
    }
    if (stats)
    {
        print_statistics(&v);
    }
    if (out_)
    {
        if (access(out, F_OK) == -1)
        {
            op = fopen(out, "w");
            write_out_file(op, &v);
            return 0;
        }
        else
        {
            if (strstr(out, ".txt\0") != NULL)
            {
                op = fopen(out, "w");
                write_out_file(op, &v);
                return 0;
            }
            else
            {
                write_out_file(stdout, &v);
                fprintf(stderr, "gameoflife: cannot overwrite non-text files. Printed to screen instead\n");
                exit(1);
            }
        }
    }
    else
    {
        write_out_file(stdout, &v);
    }

    return 0;
}
