#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PART_2

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    printf("%s", msg);
    exit(-1);
}

int get_priority(char item) {
    if(item > 96 && item < 123) 
        return item - 96;
    return item - 65 + 27;
}

int k, sum;
char backpack[256], groups[3][256];

int main(void) {
    FILE* in= fopen("input.txt", "r");
    err_n_die(in == NULL, "Couldn't find the input.txt file.\n");

#ifdef PART_1
    while(fgets(backpack, sizeof(backpack), in)) {
        bool still_checking = true;
        size_t len = strlen(backpack);
        
        for(int i=0; i<len/2 && still_checking; i++)
            for(int j=len/2; j<len && still_checking; j++)
                if(backpack[i] == backpack[j]) {
                    still_checking = false;
                    sum += get_priority(backpack[i]);
                    break;
                }
    }
#else
    while(fgets(groups[k], sizeof(groups[k]), in)) {
        if(k == 2) {
            k = 0;
            bool still_checking = true;

            for(int i=0; i<strlen(groups[0]) && still_checking; i++)
                for(int j=0; j<strlen(groups[1]) && still_checking; j++)
                    for(int l=0; l<strlen(groups[2]) && still_checking; l++)
                        if(groups[0][i] == groups[1][j] && groups[1][j] == groups[2][l]) {
                            still_checking = false;
                            sum += get_priority(groups[0][i]);
                            break;
                        }
        } else {
            k++;
        }
    }
#endif
    err_n_die(!feof(in), "Error reading the file.\n");

    printf("Answer: %d\n", sum);

    fclose(in);
    return 0;
}

