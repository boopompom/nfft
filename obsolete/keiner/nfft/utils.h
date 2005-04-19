/** Header for utilities.
 *  functions for vectors, window functions, ...
 */

#ifndef utils_h_inc
#define utils_h_inc

#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
//#include <time.h>

#include "options.h"

/** Macros
 */
#define SWAPC(x,y) {fftw_complex* temp; temp=(x); (x)=(y); (y)=temp;}
#define PI 3.1415926535897932384
#define MAX(a,b) ((a)>(b)? (a) : (b))

/** @defgroup little_group Group for little helpers
 * This group contains little helpers, e.g. for
 * timing, ...
 * @{ 
 */

/** Actual used CPU time in seconds.
 *  Calls getrusage, limited accuracy
 */
double second();

/** Computes /f$n\ge N/f$ such that /f$n=2^j,\, j\in\mathhb{N}_0/f$.
 */
int next_power_of_2(int N);

/** Computes integer /f$\prod_{t=0}^{d-1} v_t/f$.
 */
int nfft_prod_int(int *vec, int d);

/** Computes /f$\sum_{t=0}^{d-1} i_t \prod_{t'=t+1}^{d-1} N_{t'}/f$.
 */
int nfft_plain_loop(int *idx,int *N,int d);

/** Computes double /f$\prod_{t=0}^{d-1} v_t/f$.
 */
double nfft_prod_real(double *vec,int d);

/** @} 
 */ 

/** @defgroup window_group Group for window function routines
 * This group contains routines regarding window functions
 * @{ 
 */

/** Sinus cardinalis
 *  \f$\frac{sin\left(x\right)}{x}$ 
 */
double sinc(double x);

/** To test the new one
 */
double bspline_old(int k,double x,double *A);

/** Computes \f$M_{k,0}\left(x\right)\f$
 *  scratch is used for de Boor's scheme
 */
double bspline(int k, double x, double *scratch);

/** Modified Bessel function of order zero.
 *  Cephes Math Library Release 2.8:  June, 2000
 *  Copyright 1984, 1987, 2000 by Stephen L. Moshier
 */
double i0(double x);

/** @} 
 */ 

/** @defgroup vector_group Group for vector routines
 * This group contains routines for handling vectors
 * @{ 
 */

/** Computes the inner/dot product \f$x^H x\f$.
 */
double dotproductc(fftw_complex* x, int n);

/** Computes the weighted inner/dot product \f$x^H (w \odot x)\f$.
 */
double dotproductc_w(fftw_complex* x, double* w, int n);

/** Copies \f$x \leftarrow y\f$.
 */
void copyc(fftw_complex* x,fftw_complex* y, int n);

/** Copies \f$x \leftarrow a y\f$.
 */
void copyc_a(fftw_complex* x,double a, fftw_complex* y, int n);

/** Copies \f$x \leftarrow w\odot y\f$.
 */
void copyc_w(fftw_complex* x,double* w,fftw_complex* y, int n);

/** Updates \f$x \leftarrow a x + y\f$.
 */
void updatec_axpy(fftw_complex* x,double a, fftw_complex* y, int n);

/** Updates \f$x \leftarrow x + a y\f$.
 */
void updatec_xpay(fftw_complex* x,double a, fftw_complex* y, int n);

/** Updates \f$x \leftarrow a x + b y\f$.
 */
void updatec_axpby(fftw_complex* x, double a, fftw_complex* y, double b,
		   int n);

/** Updates \f$x \leftarrow x + a w\odot y\f$.
 */
void updatec_xpawy(fftw_complex* x,double a, double* w, fftw_complex* y,
		   int n);

/** computes \f$\frac{\|x_0-x\|_{\infty}}{\|x\|_{\infty}} \f$
 */
double error(double *x0, double *x, int n);

/** computes \f$\frac{\|x_0-x\|_{\infty}}{\|x\|_{\infty}} \f$
 */
double errorc(fftw_complex *x0, fftw_complex *x, int n);

/** computes \f$\frac{\|x_0-x\|_{\infty}}{\|\hat f\|_1} \f$
 */
double E_infty_error_c(fftw_complex *x0, fftw_complex *x, int M,
			  fftw_complex *f_hat, int N_d);

/** computes \f$\frac{\|x_0-x\|_2}{\|x\|_2} \f$
 */
double E_2_error_c(fftw_complex *x0, fftw_complex *x, int M);

/** vector print
 */
void vpr(double *x, int n, char *text);

/** vector print
 */
void vpr_c(fftw_complex *x, int n, char *text);

/** vector print
 */
void vpr_int(int *x, int n, char *text);

/** @} 
 */ 

/** @defgroup dampinggroup Group for damping factors in iterative reconstruction
 * This group contains sub routines for different one dimensional damping
 * factors.
 * @{ 
 */

/** Computes non periodic voronoi weights 
 *  assumes ordered x_j */
void voronoi_weights_1d(double *w, double *x, int M);

/** Computes the damping factor for the modified Fejer kernel.
 *  /f$\frac{2}{N}\left(1-\frac{\left|2k+1\right|}{N}\right)/f$
 */
double modified_fejer(int N,int kk);

/** Computes the damping factor for the modified Jackson kernel.
 */
double modified_jackson2(int N,int kk);

/** Computes the damping factor for the modified generalised Jackson kernel.
 */
double modified_jackson4(int N,int kk);

/** Computes the damping factor for the modified Sobolev kernel.
 */
double modified_sobolev(double mu,int kk);

/** Computes the damping factor for the modified multiquadric kernel.
 */
double modified_multiquadric(double mu,double c,int kk);

/** @} 
 */ 
#endif
