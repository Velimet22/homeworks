#include <stdio.h>
#include <stdlib.h>

void regression(double *x, double *y, int n, double *a0, double *b0) {
	double d11, d12, d21, d22 = n, c1, c2;
	for (int i = 0; i < n; i++) {
		d11 += x[i] * x[i];
		d12 += x[i];
		c1 += x[i] * y[i];
		c2 += y[i];
	}
	
	*a0 = (c1 * d22 - c2 * d12) / (d11 * d22 - d12 * d12); // метод Крамера
	*b0 = (c2 * d11 - c1 * d12) / (d11 * d22 - d12 * d12);
}

int main() {
	double a = 0.5, b = 1, a0, b0;
	int n = 100;
	double x[n], y[n];
	double x_min = 0, x_max = 10;
	double err, eps = 1e-15;
	
	for (int i = 0; i < n; i++) {
		x[i] = x_min + ((x_max - x_min) * rand()) / RAND_MAX;
		err = eps * ((2.0 * rand()) / RAND_MAX - 1.0);
		y[i] = a*x[i] + b + err;
	}
	
	regression(x, y, n, &a0, &b0);
	
	printf("%le %le\n", a - a0, b - b0);
	
	return 0;
}
