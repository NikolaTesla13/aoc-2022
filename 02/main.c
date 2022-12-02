#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROCK 'X'
#define PAPER 'Y'
#define SCISSORS 'Z'

void err_n_die(bool cond, char* msg) {
    if(!cond) return;
    printf("%s", msg);
    exit(-1);
}

int get_shape_score(char op, char state) {
    switch(state) {
    case 'Z': // win
        if(op == 'A') 
            return 2;
        if(op == 'B')
            return 3;
        return 1;
    case 'Y': // draw
        if(op == 'A')
            return 1;
        if(op == 'B')
            return 2;
        return 3;
    case 'X': // lose
        if(op == 'A')
            return 3;
        if(op == 'B')
            return 1;
        return 2;
    }
}

int score, new_score;
char line[4];

int main(void) {
    FILE* in= fopen("input.txt", "r");
    err_n_die(in == NULL, "Couldn't find the input.txt file.\n");

    while(fgets(line, sizeof(line), in)) {
        if(line[0] == '\n') continue;
        char opponent = line[0];
        char me = line[2];
        
        switch(me) {
        case 'X':
            new_score += 0;
            new_score += get_shape_score(opponent, 'X');
            break;
        case 'Y':
            new_score += 3;
            new_score += get_shape_score(opponent, 'Y');
            break;
        case 'Z':
            new_score += 6;
            new_score += get_shape_score(opponent, 'Z');
            break;
        }

        switch(opponent) {
        case 'A': // rock
            if(me == ROCK) 
                score += 1 + 3;
            else if(me == PAPER)
                score += 2 + 6;
            else if(me == SCISSORS)
                score += 3 + 0;
            break;

        case 'B': // paper
            if(me == ROCK)
                score += 1 + 0;
            else if(me == PAPER)
                score += 2 + 3;
            else if(me == SCISSORS)
                score += 3 + 6;
            break;

        case 'C': // scissors
            if(me == ROCK)
                score += 1 + 6;
            else if(me == PAPER)
                score += 2 + 0;
            else if(me == SCISSORS)
                score += 3 + 3;
            break;
        }
    }
    err_n_die(!feof(in), "Error reading the file.\n");

    printf("Answer 1: %d\nAnswer 2: %d\n", score, new_score);
    
    fclose(in);
    return 0;
}

