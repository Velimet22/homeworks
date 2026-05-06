#include <stdio.h>
#include <math.h>

double f(double x) {
    return sin(x);
}

double fln(double x) {
	if (x == 0) return 0;
	return 1.0 / x;
}

double fx(double x) {
	return 10.0 / (1 + 25*x*x);
}

double evalues(double a, double b, int i) {
	switch (i) {
		case 0:
			return cos(a) - cos(b);
		case 1:
			return log(b) - log(a);
		case 2:
			return 2 * atan(5*b) - 2 * atan(5*a);
	}
}

double chebesh(double a, double b, double (*f)(double)) {
    return ((b - a) / 3.0) * (f((a + b) / 2.0 - (sqrt(2.0) / 4.0) * (b - a)) + f((a + b) / 2.0) + f((a + b) / 2.0 + (sqrt(2.0) / 4.0) * (b - a)));
}

double integral(double a, double b, double eps, double h, double functions(double)) {
	double sum, i1, i2, delta, chi, mid, garant, x = a, count = 0;
	while (x < b) {

		
		i1 = chebesh(x, x + h, functions);
		i2 = chebesh(x, x + h/2.0, functions) + chebesh(x + h/2.0, x + h, functions);
 
		if (x + h < b) {
			delta = (i2 - i1) / 15.0;
			garant += fabs(delta);
			mid += delta;	
		}
		

		if (delta < eps) {
			if (x + h > b) { 
				h = b - x;
				i2 = chebesh(x, x + h/2.0, functions) + chebesh(x + h/2.0, x + h, functions);
	        	sum += i2;
				break;
			}
			
	        x += h;
			count++;
	    }

		chi = pow(fabs(delta)/eps, 1.0/5.0);
		if (chi > 10) chi = 10;
		if (chi < 0.1) chi = 0.1;
		h = 0.95 * h / chi;
	}

	return count;
}

int main() {
	double a = 1, b = 10;
	double eps = 1e-7, h = 0.1;
	
	double x = a;
	int count1 = 0, count2 = 0;
	char *text[] = {"sin", "1 / x", "10 / (1 + 25x^2)"};
	double eps_list[] = {1e-7, 1e-9, 1e-11};

	double (*functions[3])(double) = {f, fln, fx};

	printf("Введите a, b: ");
	scanf("%le%le", &a, &b);

	for (int i = 0; i < 3; i++) {
		printf("%s\n", text[i]);
		for (int j = 0; j < 2; j++) {
			count1 = integral(a, b, eps_list[j], h, functions[i]);
			count2 = integral(a, b, eps_list[j+1], h, functions[i]);
			printf("Число принятых шагов: %d\nОценка: %g\nПогрешность: %g\n\n", count1, count1*pow(100, 1.0/5.0), count1*pow(100, 1.0/5.0) - count2);
		}	
	}

    return 0;
}
