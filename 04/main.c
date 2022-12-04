#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    printf("%s", msg);
    exit(-1);
}

struct section {
    int begin;
    int end;
};

struct section read_section(char* line, char delimiter) {
    struct section s;
    char temp[50];
    int len = 0, start = 0;
    bool first_done = false;

    if(delimiter == '\n') {
        for(int j=0; j<strlen(line); j++)
            if(line[j] == ',') {
                start = j+1;
                break;
            }
    }

    for(int i=start; line[i] != delimiter && i < strlen(line); i++) {
        if(first_done) {
           temp[len++] = line[i]; 
        } else 
        if(line[i] != '-') 
            temp[len++] = line[i];
        else {
            first_done = true;
            temp[len++] = '\0';
            s.begin = atoi(temp);
            len = 0;
        }
    }
    temp[len++] = '\0';
    s.end = atoi(temp);
    
    return s;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int count, count2;
char line[256];

int main(void) {
    FILE* in= fopen("input.txt", "r");
    err_n_die(in == NULL, "Couldn't find the input.txt file.\n");

    while(fgets(line, sizeof(line), in)) {
        struct section one = read_section(line, ',');
        struct section two = read_section(line, '\n');

        if((one.begin <= two.begin && one.end >= two.end) || (two.begin <= one.begin && two.end >= two.end))
            count++;

        if(min(one.end, two.end) >= max(one.begin, two.begin))
            count2++;
    }
    err_n_die(!feof(in), "Error reading the file.\n");

    printf("Answer 1: %d\nAnswer 2: %d\n", count, count2);
    
    fclose(in);
    return 0;
}

