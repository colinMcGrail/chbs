.PHONY: clean

chbs: chbs.o wordtable.o
	$(CC) chbs.o wordtable.o -o chbs

wordtable.o: wordtable.c
	$(CC) $(CFLAGS) -c wordtable.c

wordtable.c: format.awk wordlist.txt
	awk -f format.awk wordlist.txt > wordtable.c

chbs.o: chbs.c text.h
	$(CC) $(CFLAGS) -c chbs.c

clean:
	rm -f *.o chbs wordtable.c
