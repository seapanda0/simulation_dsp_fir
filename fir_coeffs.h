#ifndef FIR_COEFFS_H
#define FIR_COEFFS_H

#include <stdint.h>

/* FIR Low-Pass Filter Coefficients
 * Fs     = 1e+03 Hz
 * Fc     = 50 Hz
 * Taps   = 8
 * Format = Q1.7 (int8, scale = 128)
 * To recover float: coeff / 128.0f
 *
 * Float reference:
 *   0.017406  0.061207  0.166164  0.255222  0.255222  0.166164  0.061207  0.017406
 */

#define N_TAPS  8
#define Q_SCALE 128

#define COEFF_0  0x02  /*    2 -> +0.015625  (float: +0.017406) */
#define COEFF_1  0x08  /*    8 -> +0.062500  (float: +0.061207) */
#define COEFF_2  0x15  /*   21 -> +0.164062  (float: +0.166164) */
#define COEFF_3  0x21  /*   33 -> +0.257812  (float: +0.255222) */
#define COEFF_4  0x21  /*   33 -> +0.257812  (float: +0.255222) */
#define COEFF_5  0x15  /*   21 -> +0.164062  (float: +0.166164) */
#define COEFF_6  0x08  /*    8 -> +0.062500  (float: +0.061207) */
#define COEFF_7  0x02  /*    2 -> +0.015625  (float: +0.017406) */

static const int8_t fir_coeffs[N_TAPS] = {
    (int8_t)COEFF_0  /*    2 */,
    (int8_t)COEFF_1  /*    8 */,
    (int8_t)COEFF_2  /*   21 */,
    (int8_t)COEFF_3  /*   33 */,
    (int8_t)COEFF_4  /*   33 */,
    (int8_t)COEFF_5  /*   21 */,
    (int8_t)COEFF_6  /*    8 */,
    (int8_t)COEFF_7  /*    2 */
};

/*
 * Verilog testbench load sequence
 * Send coeff[7] first, coeff[0] last
 *
 * cycle 1 : send 8'h02  (coeff[7] = 2)
 * cycle 2 : send 8'h08  (coeff[6] = 8)
 * cycle 3 : send 8'h15  (coeff[5] = 21)
 * cycle 4 : send 8'h21  (coeff[4] = 33)
 * cycle 5 : send 8'h21  (coeff[3] = 33)
 * cycle 6 : send 8'h15  (coeff[2] = 21)
 * cycle 7 : send 8'h08  (coeff[1] = 8)
 * cycle 8 : send 8'h02  (coeff[0] = 2)
 */

#endif /* FIR_COEFFS_H */
