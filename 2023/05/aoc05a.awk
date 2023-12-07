#!/usr/bin/awk -f
/seeds: / {
    for(i=2 ; i<=NF;i++) {
        seeds[$i]=1
    }
}

/map:/ {
    map_num++
    map_name[map_num] = $1 # numbered to iterate through the chain in map order
}

NF==3 {
    src = $2
    size = $3
    dest = $1
    maps[map_num][src][size] = dest
}

END {
    min_loc=-1

    for(s in seeds) {
        next_link = s
        for(m=1 ; m <= map_num; m++) {
            # print(map_name[m]"::")
            for(src in maps[m]) { # we could sort "src" to search more efficiently but it's a dose in awk, search linearly
                # print(map_name[m]":" next_link " : src=" src)
                src+=0 # coerce type
                found = 0
                for(size in maps[m][src]) {
                    size+=0
                    # print(map_name[m]":" next_link " : src=" src " size=" size)
                    if((next_link >= src) && (next_link < src+size)) {
                        found = 1
                        dest = maps[m][src][size]
                        dest += 0
                        new_next_link = dest + (next_link - src)
                        # print(map_name[m]":" next_link " : src=" src " size=" size " dest=" dest)
                        # print(map_name[m] ":" next_link "->" new_next_link)
                        next_link = new_next_link
                        break
                    }
                }
                if(found){
                    break
                }
            }
            # print(map_name[m] ":  looking for:" next_link)
        }
        # if no mapping was found, use unmapped "next_link"
        # print("seed:" s "-> " next_link)
        if((min_loc == -1) || (min_loc > next_link))
            min_loc = next_link
    }
    print("aoc05a: minimum loccation " min_loc)
}


