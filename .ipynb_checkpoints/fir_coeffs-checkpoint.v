// FIR Coefficients — Fs=1e+03Hz Fc=50Hz 12 taps Q1.7
// Float reference: 0.008260  0.019310  0.051067  0.098457  0.146382  0.176525  0.176525  0.146382  0.098457  0.051067  0.019310  0.008260

// Verilog localparams
localparam signed [7:0] COEFF_0 = 8'sd1;
localparam signed [7:0] COEFF_1 = 8'sd2;
localparam signed [7:0] COEFF_2 = 8'sd7;
localparam signed [7:0] COEFF_3 = 8'sd13;
localparam signed [7:0] COEFF_4 = 8'sd19;
localparam signed [7:0] COEFF_5 = 8'sd23;
localparam signed [7:0] COEFF_6 = 8'sd23;
localparam signed [7:0] COEFF_7 = 8'sd19;
localparam signed [7:0] COEFF_8 = 8'sd13;
localparam signed [7:0] COEFF_9 = 8'sd7;
localparam signed [7:0] COEFF_10 = 8'sd2;
localparam signed [7:0] COEFF_11 = 8'sd1;

// Testbench load sequence (coeff[7] first, coeff[0] last)
// cycle 1 : send 8'h01  (coeff[11] = 1)
// cycle 2 : send 8'h02  (coeff[10] = 2)
// cycle 3 : send 8'h07  (coeff[9] = 7)
// cycle 4 : send 8'h0D  (coeff[8] = 13)
// cycle 5 : send 8'h13  (coeff[7] = 19)
// cycle 6 : send 8'h17  (coeff[6] = 23)
// cycle 7 : send 8'h17  (coeff[5] = 23)
// cycle 8 : send 8'h13  (coeff[4] = 19)
// cycle 9 : send 8'h0D  (coeff[3] = 13)
// cycle 10 : send 8'h07  (coeff[2] = 7)
// cycle 11 : send 8'h02  (coeff[1] = 2)
// cycle 12 : send 8'h01  (coeff[0] = 1)
