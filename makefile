SRC=graph_basic.c graph_print.c graphaux.c
OBJ=graph_basic.o graph_print.o graphaux.o

CC = g++
CCFLAGS = -g -DLINUX

obj:	$(OBJ)

doc:	graphes.dox $(SRC)
	doxygen graphes.dox

clean:
	rm -f $(OBJ); rm -f *.exe

.SUFFIXES:	.exe

.c.exe:	
	$(CC) $(CCFLAGS) $< $(OBJ) -lm -o $@

graphaux.o:	graphes.h graphaux.h graphaux.c
	$(CC) $(CCFLAGS) -c graphaux.c

graph_basic.o:	graphes.h graphaux.h graph_basic.c
	$(CC) $(CCFLAGS) -c graph_basic.c

graph_print.o:	graphes.h graphaux.h graph_print.c
	$(CC) $(CCFLAGS) -c graph_print.c




