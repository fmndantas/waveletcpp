main: main.o wavelet.o
	@echo "-> main.out"
	@g++ -o main.out main.o wavelet.o
	@echo "Rodando testes da classe Wavelet"
	@./main.out

main.o:
	@echo "-> main.o"
	@g++ main.cpp -c

wavelet.o:
	@echo "-> wavelet.o"
	@g++ wavelet.cpp -c

clean:
	rm *.o *.out
