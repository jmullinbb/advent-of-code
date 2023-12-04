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

int main(void)
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
    printf("total:%d\n", sum);
    return 0;
}

