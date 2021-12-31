CC=c99

all: multif

multif: multif.o
	${CC} -o multif multif.o

clean:
	rm -f multif.o multif
