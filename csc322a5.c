#include  <stdio.h>

int main (int argc, char *argv[]){
    FILE *inFile;
    inFile = fopen(argv[1], "r");
    if (inFile == NULL)
    {
        fprintf(stdout, "Error: Cannot open input file [%s].\n", argv[1]);
        return 0;
    }
    printf("%s",argv[1]);
    return 0;
}
