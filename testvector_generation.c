#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "fir_coeffs.h"

#define ENABLE_NOISE 1


int8_t data_pipeline[N_TAPS] = {0};


#define SIGNAL_TABLE_SIZE	  256						//size of sinewave table (MUST BE 2^N)
#define SIGNAL_AMPLITUDE 	  80						//10-bit scale
#define SIGNAL_OFFSET 		  128						//signal offset (10-bit ADC scale)
#define SIGNAL_FREQ			  10						//Hz (sine frequency)

#define NOISE_TABLE_SIZE	256 				        //size of noise table (MUST BE 2^N)
#define NOISE_AMPLITUDE 	20							//8-bit scale
#define NOISE_OFFSET   		20							//noise offset
#define NOISE_FREQ		    100							//Hz (noise frequency)
#define NOISE_TARGET      (NOISE_FREQ / SIGNAL_FREQ)

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

uint8_t SIGNAL_TABLE[SIGNAL_TABLE_SIZE];

#if ENABLE_NOISE == 1
uint8_t NOISE_TABLE[NOISE_TABLE_SIZE];
#endif

#define TEST_VECTOR_LINES 5120
uint8_t input_table[TEST_VECTOR_LINES];
uint8_t output_table[TEST_VECTOR_LINES];


// Table: 100hz noise on 10hz signal
// Noise and signal is both sige waves
void init_tables(){

    uint16_t i;
	double angle;
	double sine_value;
    
    for (i = 0; i < SIGNAL_TABLE_SIZE; i++) {
		angle = (2.0 * PI * i) / SIGNAL_TABLE_SIZE;
    	sine_value = sin(angle);
		SIGNAL_TABLE[i] = (uint8_t)(SIGNAL_OFFSET + SIGNAL_AMPLITUDE * sine_value);
	}

#if ENABLE_NOISE == 1
	for (i = 0; i < NOISE_TABLE_SIZE; i++) {
		angle = (2.0 * PI * i) / NOISE_TABLE_SIZE;
    	sine_value = sin(angle);
		NOISE_TABLE[i] = (uint8_t)(NOISE_OFFSET + NOISE_AMPLITUDE * sine_value);
		}
#endif

	uint8_t signal_index = 0;
    uint8_t temp;
#if ENABLE_NOISE == 1
	uint8_t noise_count = 0;
	uint8_t noise_index = 0;
#endif

    for (int i = 0; i < TEST_VECTOR_LINES; i++){
        temp = SIGNAL_TABLE[signal_index];
        #if ENABLE_NOISE == 1
        // Adding noise
            if(noise_count >= NOISE_TARGET)  {
                noise_count = 0;
        #endif
                signal_index = (signal_index + 1) & (SIGNAL_TABLE_SIZE - 1);
        #if ENABLE_NOISE == 1
                }
            temp += NOISE_TABLE[noise_index];
            noise_index = (noise_index + 1) & (NOISE_TABLE_SIZE - 1);
            noise_count++;
        #endif

        input_table[i] = temp;
    }
}


uint8_t compute_fir (uint8_t data_in){

    int32_t output_temp;

    uint8_t output;

	data_pipeline[0] = data_in - 128;

	output_temp =  (int32_t)data_pipeline[0]*(int32_t)fir_coeffs[0];
	output_temp += (int32_t)data_pipeline[1]*(int32_t)fir_coeffs[1];
	output_temp += (int32_t)data_pipeline[2]*(int32_t)fir_coeffs[2];
	output_temp += (int32_t)data_pipeline[3]*(int32_t)fir_coeffs[3];
	output_temp += (int32_t)data_pipeline[4]*(int32_t)fir_coeffs[4];
	output_temp += (int32_t)data_pipeline[5]*(int32_t)fir_coeffs[5];
	output_temp += (int32_t)data_pipeline[6]*(int32_t)fir_coeffs[6];
	output_temp += (int32_t)data_pipeline[7]*(int32_t)fir_coeffs[7];

	output_temp = output_temp >> 7;
	if (output_temp > 127) output_temp = 127;
	if (output_temp < -128) output_temp = -128;

	output = output_temp;

    output = (uint8_t)(output_temp + 128);

	data_pipeline[7] = data_pipeline[6];
	data_pipeline[6] = data_pipeline[5];
	data_pipeline[5] = data_pipeline[4];
	data_pipeline[4] = data_pipeline[3];
	data_pipeline[3] = data_pipeline[2];
	data_pipeline[2] = data_pipeline[1];
	data_pipeline[1] = data_pipeline[0];

    return output;
}


int main(){
    init_tables();

    FILE *fp = fopen("testvector_input.txt", "w");  // open file for writing
    FILE *fp2 = fopen("testvector_output.txt", "w");  // open file for writing
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    if (fp2 == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // i + 40 Downsamples the original frequency
    // This is not accurate reconstruction, just a quick implementation
    // TODO: Implement sampling rate input and correctly sampling from the input table
    for (int i = 0; i < TEST_VECTOR_LINES; i = i + 40 ){
        fprintf(fp, "%02X\n", input_table[i]);  // write to file
    }

    fclose(fp);

    for (int i = 0; i < TEST_VECTOR_LINES; i = i + 40 ){
        output_table[i] = compute_fir(input_table[i]); 
        // printf("%d\n", output_table[i]);
        fprintf(fp2, "%02X\n", output_table[i]);  // write to file
    }

    fclose(fp2);
    return 0;
}