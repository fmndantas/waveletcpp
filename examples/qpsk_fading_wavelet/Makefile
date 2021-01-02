CC = g++
OBJS = main
WAVELET = ../../wavelet/wavelet.cpp
FLAGS = -pass-exit-codes -Wshadow -Wall -O2 -Wno-unused-result

main: main.o wavelet.o
	${CC} ${FLAGS} -o main.out main.o wavelet.o

main.o: main.cpp
	${CC} ${FLAGS} main.cpp -c

wavelet.o: ${WAVELET}
	${CC} ${FLAGS} ${WAVELET} -c

clean:
	rm -rf *.out *.o
