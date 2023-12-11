#!/usr/bin/awk -f
NF==1 { 
    split($0, direction, "");
}

match($0, /^... = \((...), (...)\)$/, groups) {
    map[$1]["L"] = groups[1]
    map[$1]["R"] = groups[2]
}
END {
    cur = "AAA"
    while(cur != "ZZZ") {
        d = (steps++ % length(direction)) + 1
        cur = map[cur][direction[d]]
    }
    print(steps)
}
