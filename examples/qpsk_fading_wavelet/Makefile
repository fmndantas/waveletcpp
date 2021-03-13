CC = g++
OBJS = main
WAVELET = ../../wavelet/wavelet.cpp
FLAGS = -pass-exit-codes -Wshadow -Wall -O2 -Wno-unused-result

INPUT1 = ./inputs/input2_8
INPUT2 = ./inputs/input4_16
INPUT3 = ./inputs/input2_128
OUTPUT1 = ../energy/inputs/ber_qpsk_fading_wavelet_2_8
OUTPUT2 = ../energy/inputs/ber_qpsk_fading_wavelet_4_16
OUTPUT3 = ../energy/inputs/ber_qpsk_fading_wavelet_2_128

main.out: main.o wavelet.o
	${CC} ${FLAGS} -o main.out main.o wavelet.o

main.o: main.cpp
	${CC} ${FLAGS} main.cpp -c

wavelet.o: ${WAVELET}
	${CC} ${FLAGS} ${WAVELET} -c

simulate_2_8:
	./main.out < ${INPUT1} > ${OUTPUT1}

simulate_4_16:
	./main.out < ${INPUT2} > ${OUTPUT2}

simulate_2_128:
	./main.out < ${INPUT3} > ${OUTPUT3}

clean:
	rm -rf *.out *.o
