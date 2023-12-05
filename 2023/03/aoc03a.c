#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include "input.h"

#define max(a,b)            (((a) > (b)) ? (a) : (b))

int is_symbol(char ch)
{
    if((ch != '.') && !isdigit(ch) && (ch != '\0'))
        return 1;
    return 0;
}

int is_gear(char ch)
{
    return ch == '*';
}

int touches_symbol(int row, int col)
{
    if((col>0) && is_symbol(input[row][col-1]))
        return true;

    if(is_symbol(input[row][col+1]))
        return true;

    if(row > 0)
        for(int i = max(0, col-1); i <= col + 1; i++) {
            if(is_symbol(input[row-1][i]))
                return true;
        }
    if(input[row+1] != NULL)
        for(int i = max(0, col-1); i <= col + 1; i++) {
            if(is_symbol(input[row+1][i]))
                return true;
        }
    return false;
}

int aoc_a(void)
{
    int sum = 0;
    for(int row = 0; input[row] != NULL; row++) {
        for(int col = 0; input[row][col] != '\0'; col++) {
            if(isdigit(input[row][col])){
                int start_idx = col;
                int any_touched_symbol = 0;
                for(;isdigit(input[row][col]); col++) {
                    any_touched_symbol =  any_touched_symbol || touches_symbol(row, col);
                }
                col--;
                if(any_touched_symbol) {
                    int d = strtol(input[row]+start_idx, NULL, 10);
                    sum+=d;
                }
            }
        }
    }
    return sum;
}

struct location {
    int row;
    int col;
};

// given a digit within a part number, find the start
void get_part_start(int row, int col, struct location *p_loc)
{
    for(; (col >= 0) && isdigit(input[row][col]); col--) {
        ;
    }
    p_loc->row = row;
    p_loc->col = col+1;
}

// how many parts are touching this cell
int touching_parts(int row, int col, struct location start_locations[], int loc_size)
{
    // w,n,e,s - compass
    int loc_idx = 0;

    bool w = (col > 0) && (isdigit(input[row][col-1]));
    if(w) {
        get_part_start(row, col-1, &start_locations[loc_idx]);
        loc_idx++;
    }

    if(row > 0) {
        bool nw=(col > 0) && isdigit(input[row-1][col-1]);
        if(nw) {
            get_part_start(row-1, col-1, &start_locations[loc_idx]);
            loc_idx++;
        }
        bool n = isdigit(input[row-1][col]);
        if(!nw && n) {
            get_part_start(row-1, col, &start_locations[loc_idx]);
            loc_idx++;
        }
        bool ne = isdigit(input[row-1][col+1]);
        if(!n && ne) {
            get_part_start(row-1, col+1, &start_locations[loc_idx]);
            loc_idx++;
        }
    }
    
    bool e = isdigit(input[row][col+1]);
    if(e) {
        get_part_start(row, col+1, &start_locations[loc_idx]);
        loc_idx++;
    }

    if(input[row] != NULL) {
        bool sw=(col > 0) && isdigit(input[row+1][col-1]);
        if(sw) {
            get_part_start(row+1, col-1, &start_locations[loc_idx]);
            loc_idx++;
        }
        bool s = isdigit(input[row+1][col]);
        if(!sw && s) {
            get_part_start(row+1, col, &start_locations[loc_idx]);
            loc_idx++;
        }
        bool se = isdigit(input[row+1][col+1]);
        if(!s && se) {
            get_part_start(row+1, col+1, &start_locations[loc_idx]);
            loc_idx++;
        }
    }

    printf("%d parts touching (%d, %d)\n", loc_idx, row, col);
    return loc_idx;
}

long aoc_b(void)
{
    long sum = 0;
    for(int row = 0; input[row] != NULL; row++) {
        for(int col = 0; input[row][col] != '\0'; col++) {
            if(is_gear(input[row][col]))
            {
                struct location start_locations[8]; // 6 is max
                if(touching_parts(row, col, start_locations, 8) == 2) {
                    long part1 = strtol(input[start_locations[0].row]+start_locations[0].col, NULL, 10);
                    long part2 = strtol(input[start_locations[1].row]+start_locations[1].col, NULL, 10);
                    long ratio = part1*part2;
                    sum+=ratio;
                }
            }
        }
    }
    return sum;
    return 0;
}

int main(void)
{
    printf("aoc a: %d\n", aoc_a());
    printf("aoc b: %ld\n", aoc_b());
    return 0;
}

