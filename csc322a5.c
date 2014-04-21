#include  <stdio.h>
/*#include  <stdlib.h> */

int n_city;

typedef struct{
	double time;
	int transactions;
} intfloat;

char* getError(int fcity, int lcity, double dist);
void avgRoutePrint(FILE *outFile, intfloat routes[n_city][n_city]);

int main (int argc, char *argv[]){
    FILE *inFile,*outFile;
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
	intfloat routes[n_city][n_city];
	int i,j;
	for (i = 0; i<n_city; i++)
	{
		for (j = 0; j<n_city; j++)
		{
			routes[i][j].time = 0.0;
			routes[i][j].transactions = 0;
		}
	}	
	int count=0;
	int tempf,templ;
	double tempD;
	while (!feof(inFile))
	{
		int fcity, lcity;
		double dist;
		char* error = "";
		fscanf(inFile, "%d", &fcity);
		fscanf(inFile, "%d", &lcity);
		fscanf(inFile, "%lf", &dist);
		if (!(tempf == fcity && templ == lcity && tempD == dist))
		{
			error = getError(fcity,lcity,dist);
			if (error && error[0] == '\0')
			{
				routes[fcity-1][lcity-1].time += dist;
				routes[fcity-1][lcity-1].transactions += 1;
				fprintf(outFile, "%2d %2d %5.2f\n", fcity,lcity,dist);
				count += 1;
			}
			else
				fprintf(outFile, "%2d %2d %5.2f %s\n", fcity,lcity,dist,error);
			tempf = fcity;
			templ = lcity;
			tempD = dist;
		}
	}
	fprintf(outFile, "\nNumber of valid records: %d\n\n",count);
	avgRoutePrint(outFile, routes);
	
    return 1;
}
char* getError(int fcity, int lcity, double dist){
	char* error = "";
	if (fcity > n_city)
			error = "Error: Invalid source city.";
		else if (lcity > n_city)
			error = "Error: Invalid destination city.";
		else if (fcity == lcity)
			error = "Error: Duplicated source and destination.";
		else if (dist < 0)
			error = "Error: Invalid time.";
	return error;
}
void avgRoutePrint(FILE *outFile, intfloat routes[n_city][n_city])
{
	int i,j;
	for (i = 0; i<n_city;i++){
		for (j = 0; j<n_city;j++){
			if (i != j)
			{
				if (routes[i][j].time == 0.0)
					fprintf(outFile,"From city %2d to city %2d: --\n",i+1, j+1);
				else
				{
					double avg = routes[i][j].time/routes[i][j].transactions;
					/* char *string = malloc(sizeof(double));
					double xyz;
					sprintf(string, "%5.2f", avg);
					xyz = atof(string);

					if (avg > xyz)
						avg += 0.001;

					free(string); */

					fprintf(outFile,"From city %2d to city %2d: %5.2f (%d)\n", i+1,j+1,avg, routes[i][j].transactions);
				}
			}
		}
		if (i != n_city -1)
			fprintf(outFile,"\n");
	}
}

