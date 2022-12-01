#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    printf("%s", msg);
    exit(-1);
}

int elves, items[1001], max1, max2, max3;
char line[256];

int main(void) {
    FILE* in= fopen("input.txt", "r");
    err_n_die(in == NULL, "Couldn't find the input.txt file.\n");

    while(fgets(line, sizeof(line), in)) {
        if(line[0] != '\n') {
            items[elves] += atoi(line);
        } else {
            if(items[elves] >= max1) {
                max3 = max2;
                max2 = max1;
                max1 = items[elves];
            } else if(items[elves] >= max2) {
                max3 = max2;
                max2 = items[elves];
            } else if(items[elves] > max3) {
                max3 = items[elves];
            }
            elves++;
        }
    }
    err_n_die(!feof(in), "Error reading the file.\n");

    printf("Answer: %d\n", max1 + max2 + max3);
    
    fclose(in);
    return 0;
}

