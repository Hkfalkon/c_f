c4:	main.o board.o draw.o
	cc main.o board.o draw.o -lncursesw -o c4

draw.o:	draw.c draw.h
	cc -c draw.c -Wall

board.o:	board.c board.h draw.h
	cc -c board.c -Wall

main.o:	main.c board.h draw.h
	cc -c main.c -Wall

.PHONY:	clean distclean

clean:
	-rm *.o

distclean:	clean
	-rm c4
