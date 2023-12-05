#!/usr/bin/awk -f
{
    delete winner
    num_winners=0

    $0=gensub(/:/,"","g")
    cur = $2
    copies[cur]++

    for(i=3 ; $i != "|" ;i++) {
        winner[$i]=0
    }
    for(i=i+1; i<=NF;i++) {
        if($i in winner) {
            num_winners++
        }
    }
    for(i = 1; i <= num_winners; i++) {
        card = cur+i
        copies[card] += copies[cur]
    }
}
END{
    for(i in copies) {
        # print(i ":" copies[i])
        SUM+=copies[i]
    }
    print(SUM)
}

