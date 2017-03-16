CC = gcc
LD = gcc
CFLAGS = -Wall -O2 -march=native -fopenmp -ffast-math
LDFLAGS = 
LIBS = -lm
RM = /bin/rm -f
CFLAGS2 = -Wall -O3 -march=native -fopenmp -ffast-math
OBJS = decrypt.o file_utils.o utils.o timings.o funcs_opt.o
SERIALOBJS = decryptS.o file_utils.o utilsS.o timings.o funcs_optS.o
SERIAL = -Wall -O2 -march=native -ffast-math
SERIAL2 = -Wall -O3 -march=native -ffast-math

EXECUTABLE = decrypt

all:$(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -fopenmp -o $(EXECUTABLE)

serial: $(SERIALOBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(EXECUTABLE)

decrypt.o: decrypt.c file_utils.h utils.h funcs_opt.h timings.h
	$(CC) $(CFLAGS2) -c decrypt.c

decryptS.o: decrypt.c file_utils.h utils.h funcs_opt.h timings.h
	$(CC) $(SERIAL) -c decrypt.c

file_utils.o: file_utils.c file_utils.h
	$(CC) $(CFLAGS) -c file_utils.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

utilsS.o: utils.c utils.h
	$(CC) $(SERIAL) -c utils.c

funcs_opt.o: funcs_opt.c funcs_opt.h
	$(CC) $(CFLAGS2) -c funcs_opt.c

funcs_optS.o: funcs_opt.c funcs_opt.h
	$(CC) $(SERIAL2) -c funcs_opt.c

timings.o: timings.c timings.h
	$(CC) $(CFLAGS) -c timings.c

clean:
	$(RM) $(EXECUTABLE) $(OBJS) $(SERIALOBJS) *~

