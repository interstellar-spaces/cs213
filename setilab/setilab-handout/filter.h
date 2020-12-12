#ifndef _filter
#define _filter

/*

  Basic 1D FIR filter generation by windowing,
  Hamming windows
  Basic convolution
  
  order - filter order (must be even, filter (will have order+1 coeffs)
  Fs    - Sample rate
  Fc    - Critical frequency
  Fcl     Low and 
  Fch   - High critical frequencies for band pass 
          and band stop (notch) filters

Typical use

  double Fs, Fc;
  int order;
  int N;
  double coeffs[order+1];
  double input_signal[N];
  double output_signal[N];

  // Make filter once
  generate_low_pass(Fs,Fc,order,coeffs);
  hamming_window(order, coeffs);

  // Use filter repeatedly
  while (1) {
    get_signal(input_signal,N);
    convolve(N,input_signal,order,coeffs,output_signal);
    put_signal(output_signal,N);
  }
    
*/


// Basic filter generation (based on finite, causal sincs)
// coeffs array is filled out, must have room for order+1 doubles
int generate_low_pass(double Fs, double Fc, 
		      int order, double coeffs[]);
int generate_high_pass(double Fs, double Fc, 
		       int order, double coeffs[]);
int generate_band_pass(double Fs, double Fcl, double Fch, 
		       int order, double coeffs[]);
int generate_band_stop(double Fs, double Fcl, double Fch, 
		       int order, double coeffs[]);

// Hamming window smoothing of filter
// coeffs[] array is overwritten. must have order+1 doubles
int hamming_window(int order, double coeffs[]);

// Simple (slow) convolution
// output must be same length as input.  
int convolve(int length, double input_signal[], 
	     int order, double coeffs[], 
	     double output_signal[]);

// Simple (slow) convolution combined with power estimate for output
int convolve_and_compute_power(int length, double input_signal[], 
			       int order, double coeffs[], 
			       double *power);

/* generate an n-order butterworth low-pass filter
 * [b, a] = butter(n, fcf)
 */
void butter (int n, double fcf, double ** b, double ** a);

void filter (int ord, double * a, double * b,
            int np, double * x, double * y);

/* y = filtfilt(b, a, x) */
void filtfilt (int ord, double * a, double * b,
            int np, double * x, double * y);



#endif
