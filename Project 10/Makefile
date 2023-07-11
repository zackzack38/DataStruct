readline.o: readline.h readline.c
	gcc -c readline.c

book.o: book.h book.c
	gcc -c book.c

book_requests.o: book_requests.c book.h 
	gcc -c book_requests.c

book_requests: book_requests.o readline.o book.o
	gcc -o book_requests book_requests.o book.o readline.o