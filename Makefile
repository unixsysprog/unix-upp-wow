CC     = gcc
CFLAGS = -Wall -g 


wow: wow.o wtmputil.o wtmplib.o wtmpsearch.o
	$(CC) $(CFLAGS) -o wow wow.o wtmputil.o wtmplib.o wtmpsearch.o -lm

wow.o: wow.c
	$(CC) $(CFLAGS) -c wow.c

wtmputil.o: wtmputil.c
	$(CC) $(CFLAGS) -c wtmputil.c

wtmplib.o: wtmplib.c
	$(CC) $(CFLAGS) -c wtmplib.c

wtmpsearch.o: wtmpsearch.c
	$(CC) $(CFLAGS) -c wtmpsearch.c

clean:
	rm -f wtmplib.o wtmpsearch.o wow wow.o 
