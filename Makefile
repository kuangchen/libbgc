OBJECTS = libbgc_vector.o libbgc_gas.o libbgc_collision.o libbgc_hs.o
GSL_FLAGS = -lm -lgsl -lgslcblas
DEBUG_FLAGS = -g
GPROF_FLAGS = -pg
CC = gcc

all: liblibbgc

liblibbgc: $(OBJECTS)
	$(CC) $(GSL_FLAGS) -shared -Wl,-soname,liblibbgc.so -o liblibbgc.so $(OBJECTS) 

.c.o:
	$(CC) $(DEBUG_FLAGS) -fPIC -c $<

libbgc_conservation:	$(OBJECTS) libbgc_conservation.o
	$(CC) $(GSL_FLAGS) $(DEBUG_FLAGS) $(GPROF_FLAGS) $(objects) libbgc_conservation.c liblibbgc.so -o libbgc_conservation

clean:	
	rm -rf *.o *~ *.so 