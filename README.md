# Generate FIR Filter Coefficients and Testvectors for Tiny Tapeout DSP FIR Project

### How to run
1. Run `FIR_Calc.ipynb`, this will generate `fir_coeffs.h` and `fir_coeffs.v`
2. Run `gcc testvector_generation.c -o main -lm` to generate `testvector_input.txt` and `testvector_output.txt`
3. Run `Plot_testvectors.ipynb`to visualize the input and output testvectors