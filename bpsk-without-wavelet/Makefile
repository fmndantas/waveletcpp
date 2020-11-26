main: main.o wavelet.o
	g++ -D HOME -o main.out main.o wavelet.o

main.o: main.cpp
	g++ -D HOME main.cpp -c

wavelet.o:
	g++ -D HOME ../wavelet/wavelet.cpp -c

clean:
	rm -rf *.out *.o
