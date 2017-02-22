CC=gcc

lzw : main.o trie.o comp.o descomp.o
	$(CC) -o lzw main.o trie.o comp.o descomp.o

trie.o : trie.c trie.h
	$(CC) -c trie.c     
comp.o : comp.c comp.h common.h
	$(CC) -c comp.c
descomp.o : descomp.c descomp.h common.h
	$(CC) -c descomp.c
main.o : main.c
	$(CC) -c main.c

clean :
	rm lzw main.o trie.o comp.o descomp.o
