
HEADERS = input.h

default: aoc07a aoc07b

aoc07b:
	gcc $@.o -o $@

aoc07a:
	gcc $@.o -o $@

%.o: %.c $(HEADERS)
	gcc -W -Wall -Wextra  -c $< -o $@
