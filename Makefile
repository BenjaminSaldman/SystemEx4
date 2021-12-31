CC=gcc
AR=ar
OBJECTS_MAIN=algo.o 
FLAGS= -Wall -g
all: graph
graph: $(OBJECTS_MAIN)
	$(CC) $(FLAGS) -o graph $(OBJECTS_MAIN)
algo.o: algo.c graph.h
	$(CC) $(FLAGS) -c algo.c 
.PHONY: clean all
clean:
	rm -f *.o *.a *.so graph