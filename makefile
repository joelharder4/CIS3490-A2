CC = gcc
CFLAGS = -Wall -std=c11

all: P11 P12 P21 P22

clean:
	rm -f *.o P11 P12 P21 P22

P11: P11.c
	$(CC) $(CFLAGS) P11.c -o P11

P12: P12.c
	$(CC) $(CFLAGS) P12.c -o P12

P21: P21.c
	$(CC) $(CFLAGS) P21.c -lm -o P21

P22: P22.c
	$(CC) $(CFLAGS) P22.c -lm -o P22