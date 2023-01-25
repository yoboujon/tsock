CC=gcc
CFLAGS=-Wall
SRC=src/
EXEC=main
CLEAN=clean

all: $(EXEC)

main: bal.o iptable.o main.o puit.o source.o tsock.o
	$(CC) $(CFLAGS) -o $@ $^

bal.o: src/bal.c
	$(CC) $(CFLAGS) -c $^

iptable.o: src/iptable.c
	$(CC) $(CFLAGS) -c $^

main.o: src/main.c
	$(CC) $(CFLAGS) -c $^

puit.o: src/puit.c
	$(CC) $(CFLAGS) -c $^

source.o: src/source.c
	$(CC) $(CFLAGS) -c $^

tsock.o: src/tsock.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf *.o
	rm $(EXEC)

boite:
	./$(EXEC) -b 9000

emetteur:
	./$(EXEC) -e 1 9000 localhost

recepteur:
	./$(EXEC) -r 1 9000 localhost

udpsource:
	./$(EXEC) -s -u 9000 localhost

udppuit:
	./$(EXEC) -p -u 9000

source:
	./$(EXEC) -s 9000 localhost

puit:
	./$(EXEC) -p 9000