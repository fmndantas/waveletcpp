compile_all:
	@echo "=> compiling wavelet"
	make --directory=./wavelet clean
	make --directory=./wavelet
	@echo "\n=> compiling qpsk examples"	
	make --directory=./examples/qpsk_fading clean
	make --directory=./examples/qpsk_fading
	make --directory=./examples/qpsk_fading_wavelet clean
	make --directory=./examples/qpsk_fading_wavelet
