#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGRADE 100
#define MINGRADE 0
#define NUMGRADES 101


//static FILE *f;
//static int nbins = 10;

void parse_arg(int argc, char **argv);
void operate(FILE *f);


int main(int argc, char *argv[]) {
    FILE *f;

    if (argc == 1 || !strcmp("-", argv[1])) {
        f = stdin;
    } else {
        f = fopen(argv[1], "r");
    }
    if (!f) {
        fprintf(stderr, "File not found: \"%s\"\n", argv[1]);
        return 1;
    }

    operate(f);


    return 0;
}


void operate(FILE *f){
    int grade;
    int retval;
    int count = 0;
    int students_num = 0;
    int hist[NUMGRADES] = {0};
    int median_number;

    while (1){
        retval = fscanf(f, "%d", &grade);
        if (retval == EOF) {
            break;
        } else if (retval != 1) {
            fprintf(stderr, "Error not a number");
            exit(1);
        }
        students_num++;
        if (grade<MINGRADE || grade>MAXGRADE) {
            fprintf(stderr, "Error at line %d: grade %d invalid", students_num, grade);
            exit (1);
        }
        hist[grade]++;
    }

    median_number = (students_num+1) / 2;


    for (int i = 0; i < NUMGRADES ; ++i) {
        count += hist[i];
        if (count >= median_number){
            printf("%d", grade);
            break;
        }
    }
}
