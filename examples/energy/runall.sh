#!/bin/bash

make

# qpsk without wavelet encoding
QPSK_FADING=../qpsk_fading/

# $QPSK_FADING/main.out < $QPSK_FADING/input > $QPSK_FADING/output
# ./main.out < $QPSK_FADING/output > outputs/output_qpsk_fading

# qpsk with wavelet encoding
QPSK_FADING_WAVELET=../qpsk_fading_wavelet/

# QPSK_FADING_WAVELET/main.out < $QPSK_FADING_WAVELET/inputs/input2_8 > $QPSK_FADING_WAVELET/outputs/output2_8
# ./main.out < $QPSK_FADING_WAVELET/outputs/output2_8 > ./outputs/output_qpsk_fading_wavelet_2_8

# $QPSK_FADING_WAVELET/main.out < $QPSK_FADING_WAVELET/inputs/input4_16 > $QPSK_FADING_WAVELET/outputs/output4_16
# ./main.out < $QPSK_FADING_WAVELET/outputs/output4_16 > ./outputs/output_qpsk_fading_wavelet_4_16

# $QPSK_FADING_WAVELET/main.out < $QPSK_FADING_WAVELET/inputs/input2_128 > $QPSK_FADING_WAVELET/outputs/output2_128
./main.out < $QPSK_FADING_WAVELET/outputs/output2_128 > ./outputs/output_qpsk_fading_wavelet_2_128
