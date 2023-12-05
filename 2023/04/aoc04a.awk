#!/usr/bin/awk -f
#aoc04a.awk

{
    delete winner
    num_winners=0
    for(i=3 ; $i != "|" ;i++) {
        winner[$i]=0
    }
    for(i=i+1; i<=NF;i++) {
        if($i in winner) {
            num_winners++
        }
    }
    if(num_winners) {
        SUM+= 2**(num_winners-1)
    }
}
END{print SUM}
