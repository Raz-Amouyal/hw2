#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXGRADE 100
#define MINGRADE 0

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
    int max_grade = MINGRADE;
    int students_num = 1;

    while (1){
        retval = fscanf(f, "%d", &grade);
        if (retval == EOF) {
            break;
        } else if (retval != 1) {
            fprintf(stderr, "Error not a number");
            exit(1);
        }
        if (grade<MINGRADE || grade>MAXGRADE) {
            fprintf(stderr, "Error at line %d: grade %d invalid", students_num, grade);
            exit (1);
        }
        if (max_grade > grade){
            max_grade = grade;
        }
        students_num++;
    }

    printf("%d", max_grade);
}
