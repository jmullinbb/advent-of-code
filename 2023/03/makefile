HEADERS = input.h
OBJECTS = aoc03a.o

default: aoc03a

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

program: $(OBJECTS)
	gcc $(OBJECTS) -o $@
