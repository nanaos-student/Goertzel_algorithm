#include <stdio.h>
#include <math.h>

#define SAMPLING_RATE 8000  // Replace with your actual sampling rate
#define NUM_TARGETS 8
#define NUM_SAMPLES 205

// Global variables
float magnitudes[NUM_TARGETS];
float samples[NUM_SAMPLES];
int Flag = 1;
char digit;
int v, b, m;
int high,low;
float time;
// Function prototypes
void goertzel_multi(const float samples[], int numSamples, float targetFrequencies[]);
void Frequency_detection(float magnitudes[]);
void Generate_tones(char digit);
void sample_generator(float samples[],int low,int high, int numSamples);
// Function to perform the Goertzel algorithm for multiple frequencies
void goertzel_multi(const float samples[], int numSamples, float targetFrequencies[]) {
// to be completed
	float magnitudes[NUM_TARGETS];
	short coef[8] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7, 0x4A70, 0x4090, 0x3290, 0x23CE};
	float Goertzel_Value = 0.0;
	float delay_1 = 0.0, delay_2 = 0.0, delay;
	float prod1, prod2, prod3;
	for (v = 0; v < NUM_TARGETS; ++v){
		for (b = 0; b < numSamples-1; ++b){
			float input = samples[b];;
			int input_int = (int)input;
			input_int >>= 1;
			input_int <<= 4;
			input = (float)input_int;
			prod1 = (delay_1*coef[v]) / 16384.0f;
			delay = input + prod1 - delay_2;
			delay_2 = delay_1;
			delay_1 = delay;
		}
		prod1 = (delay_1 * delay_1);
		prod2 = (delay_2 * delay_2);
		prod3 = (delay_1 * coef[v]) / 16384.0f;
		prod3 *= delay_2;
		Goertzel_Value = (prod1 + prod2 - prod3) / 32768.0f;
		Goertzel_Value /= 16.0f;
		Goertzel_Value *= 16.0f;
		delay_1 = delay_2 = 0.0;
		magnitudes[v] = Goertzel_Value;
		}
	for (m = 0; m < NUM_TARGETS; ++m){
		printf("Magnitude for frequency:%f,%f\n", targetFrequencies[m],magnitudes[m]);
	}
}

// Function to detect the maximum frequency and interpret the key pressed
void Frequency_detection(float magnitudes[]) {
// to be completed
												}

// Function to generate tones based on the pressed key
void Generate_tones(char digit)		 {
// to be completed

	switch (digit) {
	case '0': low = 941; high = 1336;
	break;
	case '1': low = 697; high = 1209;
	break;
	case '2': low = 697; high = 1336;
	break;
	case '3': low = 697; high = 1477;
	break;
	case '4': low = 770; high = 1209;
	break;
	case '5': low = 770; high = 1336;
	break;
	case '6': low = 770; high = 1477;
	break;
	case '7': low = 852; high = 1209;
	break;
	case '8': low = 852; high = 1336;
	break;
	case '9': low = 852; high = 1477;
	break;
	case 'A': low = 697; high = 1633;
	break;
	case 'B': low = 770; high = 1633;
	break;
	case 'C': low = 852; high = 1633;
	break;
	case 'D': low = 697; high = 1633;
	break;
	case '#': low = 941; high = 1477;
	break;
	}
	printf("%c,%d,%d \n",digit,low,high);
									}

void sample_generator(float samples[],int low,int high, int numSamples){
    int i;
    for (i = 0; i < numSamples; i++){
        float time = (float)i / (SAMPLING_RATE);
        samples[i] = sin(2*M_PI*time*low) + sin(2*M_PI*time*high);
    }
return;
}
int main() {
	int checker;
    while (1) {
        printf("Type a key [0,1,2,3,4,5,6,7,8,9,#,A,B,C,D] and press return:\n");
        scanf("\n%c", &digit);
        checker = (digit >= 'A' && digit <= 'D') || (digit >= '0' && digit <= '9') || digit == '#';
        if (!checker) {
        	printf("You entered the wrong character; try another character \n");
        } else {
        	Generate_tones(digit);
        }

        // Example usage
        float targetFrequencies[NUM_TARGETS] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};
        sample_generator(samples,low,high,NUM_SAMPLES);
        // Call the function to calculate magnitudes for each frequency
        goertzel_multi(samples, NUM_SAMPLES, targetFrequencies);
        printf("The key you entered is %c\n",digit);

        // Detect the maximum frequency and interpret the key pressed
        Frequency_detection(magnitudes);
    }


}
