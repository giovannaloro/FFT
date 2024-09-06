#include <math.h>
#include <complex.h>

//A simple implementation of fft for power of two size integers values
complex double * fft(int * samples, int len){
    //Return the array if the size of the array is one 
    if(len == 1){
        complex double value = samples[0] + 0*I;
        complex double * spectrum = malloc(sizeof(double complex));
        spectrum[0] = value;
        return spectrum;
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
