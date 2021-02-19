#include <bits/stdc++.h>

#define f first
#define s second
#define loop(i, n) for (int i = 0; i < n; ++i)
#define read(a, n) loop($, n) cin >> a[$];
#define show(a, n)                  \
    loop($, n) cout << a[$] << " "; \
    cout << endl;

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

/*	// RANDOM NUMBER GENERATOR
// rng() generates u.a.r. from [0, 2^32 - 1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
*/

/* // TIME
auto start = chrono::high_resolution_clock::now();
// ...
auto stop = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
cout << duration.count() << endl;
*/

const double E = exp(1.0);
const double PI = acos(-1.0);

// Complex numbers
struct cplx{
	double re, im;

	cplx operator + (const cplx& other){
		return {re + other.re, im + other.im};
	}

	cplx operator - (const cplx& other){
		return {re - other.re, im - other.im};
	}

	cplx operator * (const cplx& other){
		return {re * other.re - im * other.im, re * other.im + im * other.re};
	}
};

// Time: O(nlog(n)), Space: O(nlog(n))
// n must be power of 2
void FFT(size_t n, cplx a[], bool invert){
	if(n == 1){
		return;
	}
	size_t m = n / 2;
	cplx a_0[m];
	cplx a_1[m];
	for(size_t i = 0; i < n; ++i){
		if(i & 1){
			a_1[i / 2] = a[i];
		}else{
			a_0[i / 2] = a[i];
		}
	}
	FFT(m, a_0, invert);
	FFT(m, a_1, invert);
	double phi = (invert ? -1 : 1) * 2 * PI / n;
	cplx g = {cos(phi), sin(phi)};
	cplx w = {1.0, 0.0};
	for(size_t i = 0; i < m; ++i){
		a[i] = a_0[i] + (w * a_1[i]);
		if(invert){
			a[i].re = 0.5 * a[i].re;
			a[i].im = 0.5 * a[i].im;
		}
		a[i + m] = a_0[i] - (w * a_1[i]);
		if(invert){
			a[i + m].re = 0.5 * a[i + m].re;
			a[i + m].im = 0.5 * a[i + m].im;
		}
		w = w * g;
	}  
}

// Time: O(n), Space: O(n)
void pointwiseMultiplication(size_t n, cplx a[], cplx b[], cplx c[]){
	for(size_t i = 0; i < n; ++i){
		c[i] = a[i] * b[i];
	}
}

// Stores the convolution of a and b in c (Time: O(nlog(n)), Space: O(n))
// n must be power of 2
void convolution(size_t n, cplx a[], cplx b[], cplx c[]){
	FFT(n, a, false);
	FFT(n, b, false);
	pointwiseMultiplication(n, a, b, c);
	FFT(n, c, true);
}

// Evaluates polynomial (Time: O(n))
cplx evaluate(size_t n, cplx a[], cplx x){
	cplx p = {1.0, 0.0}, v = {0.0, 0.0};
	for(size_t i = 0; i < n; ++i){
		v = v + (a[i] * p);
		p = p * x;
	}
	return v;
}

int main(){
	
	// Multiplying 2 polynomials in O(nlog(n))
	
	// Get the degree of the polynomials
	int n;	
	scanf("%d\n", &n);

	// Compute size for coefficient arrays (smallest power of 2 large enough for product)
	int s = 2;
	while(s <= 2 * n){	
		s *= 2;
	}

	// Get coefficients of polynomials
	cplx a[s], b[s], c[s];
	memset(a, 0, s * sizeof(cplx));
	memset(b, 0, s * sizeof(cplx));
	for(int i = 0; i <= n; ++i){
		scanf("%lf", &(a[i].re));
	}
	for(int i = 0; i <= n; ++i){
		scanf("%lf", &(b[i].re));
	}

	// The coefficients of the product are the convolution of the coefficients 
	convolution(s, a, b, c);

	// Print result
	for(int i = 0; i <= 2 * n; ++i){
		printf("%lld ", (ull) (c[i].re + 0.5));
	}
	printf("\n");

	return 0;
	
}
