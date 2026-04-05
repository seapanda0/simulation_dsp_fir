// FIR Coefficients — Fs=1e+03Hz Fc=50Hz 8 taps Q1.7
// Float reference: 0.017406  0.061207  0.166164  0.255222  0.255222  0.166164  0.061207  0.017406

// Verilog localparams
localparam signed [7:0] COEFF_0 = 8'sd2;
localparam signed [7:0] COEFF_1 = 8'sd8;
localparam signed [7:0] COEFF_2 = 8'sd21;
localparam signed [7:0] COEFF_3 = 8'sd33;
localparam signed [7:0] COEFF_4 = 8'sd33;
localparam signed [7:0] COEFF_5 = 8'sd21;
localparam signed [7:0] COEFF_6 = 8'sd8;
localparam signed [7:0] COEFF_7 = 8'sd2;

// Testbench load sequence (coeff[7] first, coeff[0] last)
// cycle 1 : send 8'h02  (coeff[7] = 2)
// cycle 2 : send 8'h08  (coeff[6] = 8)
// cycle 3 : send 8'h15  (coeff[5] = 21)
// cycle 4 : send 8'h21  (coeff[4] = 33)
// cycle 5 : send 8'h21  (coeff[3] = 33)
// cycle 6 : send 8'h15  (coeff[2] = 21)
// cycle 7 : send 8'h08  (coeff[1] = 8)
// cycle 8 : send 8'h02  (coeff[0] = 2)
