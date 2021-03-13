main: main.out
	./main.out < 2 > output2

main.out: main.o wavelet.o
	g++ -pass-exit-codes -Wshadow -Wall -O2 -Wno-unused-result -o main.out main.o wavelet.o

main.o: main.cpp
	g++ -pass-exit-codes -Wshadow -Wall -O2 -Wno-unused-result main.cpp -c

wavelet.o: ../../wavelet/wavelet.cpp
	g++ -pass-exit-codes -Wshadow -Wall -O2 -Wno-unused-result ../../wavelet/wavelet.cpp -c

plot:
	python3 plot.py < output

clean:
	rm -rf *.out *.o
