SRC=graph_basic.c graph_print.c graphaux.c dijkstra.c heap.c priority_queue.c
OBJ=graph_basic.o graph_print.o graphaux.o dijkstra.o heap.o priority_queue.o

CC = g++
CCFLAGS = -g -DLINUX

obj:	$(OBJ)

doc:	graphes.dox $(SRC)
	doxygen graphes.dox

clean:
	rm -f $(OBJ); rm -f *.exe

.SUFFIXES:	.exe

.c.exe: $(OBJ)	
	$(CC) $(CCFLAGS) $< $(OBJ) -lm -o $@

dijkstra.o : graphes.h graphaux.h dijkstra.c
	$(CC) $(CCFLAGS) -c dijkstra.c

heap.o : heap.c
	$(CC) $(CCFLAGS) -c heap.c

priority_queue.o : priority_queue.c
	$(CC) $(CCFLAGS) -c priority_queue.c

graphaux.o:	graphes.h graphaux.h graphaux.c
	$(CC) $(CCFLAGS) -c graphaux.c

graph_basic.o:	graphes.h graphaux.h graph_basic.c
	$(CC) $(CCFLAGS) -c graph_basic.c

graph_print.o:	graphes.h graphaux.h graph_print.c
	$(CC) $(CCFLAGS) -c graph_print.c




