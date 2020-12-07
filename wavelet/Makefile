main: main.o wavelet.o
	@echo "-> main.out"
	@g++ -o main.out main.o wavelet.o
	@echo "-> input: test-2-128"
	@./main.out < ./test-2-128
	@echo "-> input: test-2-8"
	@./main.out < ./test-2-8
	@echo "-> input: test-4-16"
	@./main.out < ./test-4-16

main.o: main.cpp
	@echo "-> main.o"
	@g++ main.cpp -c

wavelet.o:
	@echo "-> wavelet.o"
	@g++ wavelet.cpp -c

clean:
	rm *.o *.out
