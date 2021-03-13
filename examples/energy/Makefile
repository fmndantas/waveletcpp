CC = g++
OBJS = main
FLAGS = -pass-exit-codes -Wshadow -Wall -O2 -Wno-unused-result

INPUT1 = ./inputs/ber_qpsk_fading
INPUT2 = ./inputs/ber_qpsk_fading_wavelet_2_8
INPUT3 = ./inputs/ber_qpsk_fading_wavelet_4_16

OUTPUT1 = ./outputs/energy_qpsk_fading
OUTPUT2 = ./outputs/energy_qpsk_fading_wavelet_2_8
OUTPUT3 = ./outputs/energy_qpsk_fading_wavelet_4_16
OUTPUT4 = ./outputs/energy_qpsk_fading_wavelet_2_128

simulate: main.out
	make --directory=../qpsk_fading
	make --directory=../qpsk_fading_wavelet simulate_2_8
	make --directory=../qpsk_fading_wavelet simulate_4_16
	./main.out < ${INPUT1} > ${OUTPUT1}
	./main.out < ${INPUT2} > ${OUTPUT2}
	./main.out < ${INPUT3} > ${OUTPUT3}

main.out: main.o
	${CC} ${FLAGS} -o main.out main.o

main.o: main.cpp
	${CC} ${FLAGS} main.cpp -c

clean:
	rm -rf *.out *.o
