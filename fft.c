#include <math.h>
#include <complex.h>

int next_power_oftwo(int len){
    float e = log2(e);
    int n = e;  
    return e++;
}

//A simple implementation of fft for power of two size integers values
complex double * fft(int * samples, int len){
    //Return the array if the size of the array is one 
    if(len == 1){
        complex double value = samples[0] + 0*I;
        complex double * spectrum = malloc(sizeof(double complex));
        spectrum[0] = value;
        return spectrum;
    }
    //if the input array size is not a power of two fill 0s until the size reaches the next power of two dimension 
    if(len%2 != 0){
      int filled_samples_len = 2**next_power_oftwo(len);
      int filled_samples [filled_samples_len];
      for(int i = 0; i<len ; i++){
          filled_samples[i] = samples[i];
      }
      for(int i = len ; i < filled_samples_len; i++){
          filled_samples[i] = 0;
      }
      samples = filled_samples;
      len = filled_samples_len; 
    }
    //Create an even array and an odd array of values and fill them with the odd/even elements of the array
    int even_samples[len/2];
    int odd_samples[len/2];
    for(int i = 0; i<len/2; i++){
        even_samples[i] = samples[2*i];
        odd_samples[i] = samples[2*i+1];
    }
    //Call the function for the odd/even part of the array
    double complex * even_spectrum = fft(even_samples, len/2);
    double complex * odd_spectrum = fft(odd_samples, len/2 );
    //Merge the values and return the final array of values
    double complex * output_spectrum = malloc(len*sizeof(double complex));
    for(int i = 0; i<len/2; i++){
        complex double Ck = cexp(-I*2*M_PI*i/len)*odd_spectrum[i];
        output_spectrum[i] = even_spectrum[i]+Ck; 
        output_spectrum[i+len/2] = even_spectrum[i]-Ck;
    }
    return output_spectrum;
}
