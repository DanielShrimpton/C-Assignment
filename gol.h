struct universe
{
    /*Put some appropriate things here*/
    char **cells;
};

/*Do not modify the next seven lines*/
void read_in_file(FILE *infile, struct universe *u);
void write_out_file(FILE *outfile, struct universe *u);
int is_alive(struct universe *u, int column, int row);
int will_be_alive(struct universe *u, int column, int row);
int will_be_alive_torus(struct universe *u, int column, int row);
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row));
void print_statistics(struct universe *u);
/*You can modify after this line again*/

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

    u->cells[i] = (char *)realloc(u->cells[i], 2*sizeof(char));
    u->cells[i] = '\0';

    // for (j = 0; j < i; j++)
    // {
    //     printf("%d. %s\n", j, u->cells[j]);
    // }
}