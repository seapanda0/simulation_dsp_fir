#ifndef FIR_COEFFS_H
#define FIR_COEFFS_H

#include <stdint.h>

/* FIR Low-Pass Filter Coefficients
 * Fs     = 1e+03 Hz
 * Fc     = 50 Hz
 * Taps   = 12
 * Format = Q1.7 (int8, scale = 128)
 * To recover float: coeff / 128.0f
 *
 * Float reference:
 *   0.008260  0.019310  0.051067  0.098457  0.146382  0.176525  0.176525  0.146382  0.098457  0.051067  0.019310  0.008260
 */

#define N_TAPS  12
#define Q_SCALE 128

#define COEFF_0  0x01  /*    1 -> +0.007812  (float: +0.008260) */
#define COEFF_1  0x02  /*    2 -> +0.015625  (float: +0.019310) */
#define COEFF_2  0x07  /*    7 -> +0.054688  (float: +0.051067) */
#define COEFF_3  0x0D  /*   13 -> +0.101562  (float: +0.098457) */
#define COEFF_4  0x13  /*   19 -> +0.148438  (float: +0.146382) */
#define COEFF_5  0x17  /*   23 -> +0.179688  (float: +0.176525) */
#define COEFF_6  0x17  /*   23 -> +0.179688  (float: +0.176525) */
#define COEFF_7  0x13  /*   19 -> +0.148438  (float: +0.146382) */
#define COEFF_8  0x0D  /*   13 -> +0.101562  (float: +0.098457) */
#define COEFF_9  0x07  /*    7 -> +0.054688  (float: +0.051067) */
#define COEFF_10  0x02  /*    2 -> +0.015625  (float: +0.019310) */
#define COEFF_11  0x01  /*    1 -> +0.007812  (float: +0.008260) */

static const int8_t fir_coeffs[N_TAPS] = {
    (int8_t)COEFF_0  /*    1 */,
    (int8_t)COEFF_1  /*    2 */,
    (int8_t)COEFF_2  /*    7 */,
    (int8_t)COEFF_3  /*   13 */,
    (int8_t)COEFF_4  /*   19 */,
    (int8_t)COEFF_5  /*   23 */,
    (int8_t)COEFF_6  /*   23 */,
    (int8_t)COEFF_7  /*   19 */,
    (int8_t)COEFF_8  /*   13 */,
    (int8_t)COEFF_9  /*    7 */,
    (int8_t)COEFF_10  /*    2 */,
    (int8_t)COEFF_11  /*    1 */
};

/*
 * Verilog testbench load sequence
 * Send coeff[7] first, coeff[0] last
 *
 * cycle 1 : send 8'h01  (coeff[11] = 1)
 * cycle 2 : send 8'h02  (coeff[10] = 2)
 * cycle 3 : send 8'h07  (coeff[9] = 7)
 * cycle 4 : send 8'h0D  (coeff[8] = 13)
 * cycle 5 : send 8'h13  (coeff[7] = 19)
 * cycle 6 : send 8'h17  (coeff[6] = 23)
 * cycle 7 : send 8'h17  (coeff[5] = 23)
 * cycle 8 : send 8'h13  (coeff[4] = 19)
 * cycle 9 : send 8'h0D  (coeff[3] = 13)
 * cycle 10 : send 8'h07  (coeff[2] = 7)
 * cycle 11 : send 8'h02  (coeff[1] = 2)
 * cycle 12 : send 8'h01  (coeff[0] = 1)
 */

#endif /* FIR_COEFFS_H */
