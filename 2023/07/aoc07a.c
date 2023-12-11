#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include "input.h"

#define CARD_HIGH 0
#define CARD_1_PAIR 0x01
#define CARD_2_PAIR 0x02
#define CARD_3_OK   0x04
#define CARD_FULL_HOUSE (CARD_3_OK|CARD_1_PAIR)
#define CARD_4_OK  0x08
#define CARD_5_OK  0x10

char *hand_str[] = {
    "High card", 
    "1 pair",
    "2 pair",
    "2 pair",
    "3 of a kind",
    "Full house",
    "",
    "",
    "4 of a kind",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "5 of a kind"
};

int classify_hand(struct hand *h)
{
    char tmp[6] = "";
    int card_count[5] = {0};
    int card_types = 0;
    strcpy(tmp, h->cards);
    for(int i = 0; i < 5 ; i++)
    {
        if(tmp[i] == ' ') 
        {
            continue;
        }
        card_count[card_types]++;
        for(char *p = &tmp[i+1]; *p != '\0' ; p++) 
        {
            if(*p == tmp[i]) {
                card_count[card_types]++;
                *p=' ';
            }
        }
        card_types++;
    }

    for(int i = 0; i < 5; i++ ) {
        switch(card_count[i]) {
            case 5: h->type |= CARD_5_OK; break;
            case 4: h->type |= CARD_4_OK; break;
            case 3: h->type |= CARD_3_OK; break;
            case 2: h->type |= (h->type & CARD_1_PAIR) ? CARD_2_PAIR : CARD_1_PAIR;  break;
        }
    }
    return card_types;
}

int card_rank(char card)
{
    switch(card) {
        case 'A': return 14;
        case 'K': return 13;
        case 'Q': return 12;
        case 'J': return 11;
        case 'T': return 10;
        case '9': return 9;
        case '8': return 8;
        case '7': return 7;
        case '6': return 6;
        case '5': return 5;
        case '4': return 4;
        case '3': return 3;
        case '2': return 2;
    }
    return 0;
}

int cmp_func (const void * a, const void * b) 
{
    struct hand *ha  = (struct hand*)a;
    struct hand *hb  = (struct hand*)b;
    if ( ha->type == hb->type ) {
        for(int i = 0; i<5;i++) {
            if(ha->cards[i] != hb->cards[i])
                return card_rank(ha->cards[i]) - card_rank(hb->cards[i]);
        }
    }
    return ( ((struct hand*)a)->type - ((struct hand*)b)->type );
}

long aoc_a(void)
{
    unsigned long long winnings = 0;
    for(size_t i =0; i<sizeof(input)/sizeof(input[0]) ; i++) 
    {
        classify_hand(&input[i]);
    }
    qsort(input, sizeof(input)/sizeof(input[0]), sizeof(input[0]), cmp_func);
    for(size_t i =0; i<sizeof(input)/sizeof(input[0]) ; i++) {
        // printf("%s: %d: %s\n", input[i].cards, input[i].type,hand_str[input[i].type] );
        winnings += (i+1) * input[i].bid;
    }
    printf("winnings %llu\n", winnings);
    return 0;
}

int main(void)
{
    printf("aoc a: %ld\n\n", aoc_a());
    return 0;
}

