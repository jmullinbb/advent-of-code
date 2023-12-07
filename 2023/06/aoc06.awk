#!/usr/bin/awk -f
/Time:/ { for(i = 1 ; i < NF ; i++) { race_durations[i] = $(i+1) } }
/Distance:/ { for(i = 1 ; i < NF ; i++) { distances[i] = $(i+1) } ; num_races = NF-1 }

func calc_winning_races() {
    product = 1
    for(i=1; i <= num_races; i++) {
        duration = race_durations[i]
        record_distance = distances[i]
        for (accel_time = 1; accel_time < duration ; accel_time++) {
            race_distance = accel_time * (duration-accel_time)
            if(race_distance > record_distance) {
                winning_accel_times = (duration - accel_time*2) + 1
                #print ("Race " i - 1 ": distance (" race_distance ") > record (" record_distance "): accel =" accel_time" Winning accels:" winning_accel_times )
                product *= winning_accel_times
                break
            }
        }
    }
    print( product)
}
END {
    #part 1
    calc_winning_races()
    #part 2
    for(i=1; i <= num_races; i++) {
        long_duration = (long_duration race_durations[i])
        long_distance = (long_distance distances[i])
    }
    #print ("{" long_duration "}{"long_distance"}")
    delete race_durations
    delete distances
    race_durations[1] = long_duration + 0
    distances[1] = long_distance + 0
    num_races = 1
    calc_winning_races()
}
