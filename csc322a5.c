#include  <stdio.h>
struct intfloat{
	float time;
	int transactions;
};

int main (int argc, char *argv[]){
    FILE *inFile,*outFile;
	int n_city;
	if (argv[1] == NULL)
	{
		fprintf(stdout, "Usage: csc322a5 <infile> [<outfile>]");
		return 0;
	}
    inFile = fopen(argv[1], "r");
	outFile = stdout;
    if (inFile == NULL)
    {
        fprintf(stdout, "Error: Cannot open input file [%s].\n", argv[1]);
        return 0;
    }
	if (argv[2] != NULL)
	{
		outFile = fopen(argv[2], "w");
		if (outFile == NULL)
		{
			fprintf(stdout, "Error: Cannot open output file [%s].\n", argv[2]);
			return 0;
		}
	}
	/*Make sure to use fprintf(outFile,...); for every type of output... will
	work with both an outfile and no outfile to standard output. */
	fscanf(inFile,"%d",&n_city);
	struct intfloat routes[n_city][n_city];
	
	
    return 1;
}


