#!/usr/bin/awk -f
BEGIN{SUM=0}
/Game /{
    delete max
    $0 = gensub(/[;:,]/," ","g")
    for(i = 3; i < NF ; i+=2)
    {
        if(max[$(i+1)] < $i) {
            max[$(i+1)] = $i
        }
    }
    product = 1
    #printf("Game %d:", $2)
    for(i in max) {
        #printf("%s=%d, ", i, max[i])
        product *= max[i]
    }
    SUM+=product
    #printf("product=%d SUM=%d\n", product, SUM)
}
END{print SUM}

