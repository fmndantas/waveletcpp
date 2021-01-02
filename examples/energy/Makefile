CC = g++
OBJS = main
FLAGS = -pass-exit-codes -Wshadow -Wall -O2 -Wno-unused-result

main: main.o
	${CC} ${FLAGS} -o main.out main.o

main.o: main.cpp
	${CC} ${FLAGS} main.cpp -c

clean:
	rm -rf *.out *.o
