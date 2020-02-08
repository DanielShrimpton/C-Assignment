struct universe
{
    /*Put some appropriate things here*/
    char cells[24][512];
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
    int i=0, j=0;
    while (fgets(u[0].cells[i], 512, infile)) {
        u[0].cells[i][strlen(u[0].cells[i])-1] = '\0';
        i++;
    }

    for (j=0; j<i; j++) printf("%d. %s\n", j, u[0].cells[j]);
}