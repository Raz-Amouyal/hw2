#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGRADE 100
#define MINGRADE 0

static FILE *f;
static int nbins = 10;

void parse_arg(int argc, char **argv);
void operate(int *bins);

int main(int argc, char *argv[]) {

    parse_arg(argc, argv);
    if (!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    int *bins = (int*) calloc(nbins,sizeof(int));
    operate(bins);
    free(bins);

    return 0;
}

void operate(int *bins){
    int grade;
    int retval;
    double pace;
    int line = 1;

    while (1){
        retval = fscanf(f, "%d", &grade);
        if (retval == EOF) {
            break;
        } else if (retval != 1) {
            fprintf(stderr, "Error not a number");
            exit(1);
        } else if (grade > MAXGRADE || grade < MINGRADE) {
            fprintf(stderr, "Error at line %d: grade %d invalid", line, grade);
            exit(1);
        }
        int n = (grade != 100) ? grade / (100 / nbins) : nbins -1;
	
        bins[n]++;
	line++;
    }
    pace = 100.0 / nbins;
    for (int i = 0; i < nbins ; ++i) {
        printf("%.0lf-%.0lf\t%d\n",
               i * pace,
               (i < nbins-1) ? ((i+1) * pace -1) : MAXGRADE,
               bins[i]);
    }
}

void parse_arg(int argc, char **argv){
    f = stdin;
    int c=0;
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-")){
            f = stdin;
	    c++;
        } else if (!strcmp(argv[i], "-nbins")){
            nbins = i<argc-1 ? atoi(argv[i+1]) : 10;
            i++;
        } else if(!c) {
            f = fopen(argv[i], "r");
        }
    }

}
