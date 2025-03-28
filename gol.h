struct universe
{
    /*Put some appropriate things here*/
    char **cells;
    int r, c;  // Number of rows and columns
    float curr, tot;  // ints for current/total number of cells
    float c_alive;  // int to store the current number of alive cells
    float t_alive;  // int to store the total number of alive cells
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
