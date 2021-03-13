compile_all:
	@echo "=> compiling wavelet"
	make --directory=./wavelet clean
	make --directory=./wavelet
	@echo "\n=> compiling qpsk examples"	
	make --directory=./examples/qpsk_fading clean
	make --directory=./examples/qpsk_fading
	make --directory=./examples/qpsk_fading_wavelet clean
	make --directory=./examples/qpsk_fading_wavelet

energy: ber
	make --directory=./examples/energy

ber: compile_all
	make --directory=./examples/qpsk_fading simulate
	make --directory=./examples/qpsk_fading_wavelet simulate_2_8
	make --directory=./examples/qpsk_fading_wavelet simulate_4_16

