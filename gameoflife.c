#include<stdio.h>
// #include"gol.h"
#include"gol.c"
int main(int argc, char* argv[]){
  printf("%d, %s\n", argc, argv[0]);
  struct universe v;
  FILE *fp;
  char name[100];
  fgets(name, sizeof(name), stdin);
  char *newline = strchr(name, '\n');
  if (newline)
  {
    *newline = '\0';
  }
  fp = fopen(name, "r");
  read_in_file(fp,&v);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  evolve(&v,will_be_alive);
  write_out_file(stdout,&v);
return 0;
}
