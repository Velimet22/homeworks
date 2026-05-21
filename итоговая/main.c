#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double func(double x) {
    return pow(x, 7);
    //return 1.0/3.0 * log(1 + pow(x, 4));
    //return 1 / (x + 1);
}

int sign(double x) {
    if(x>0)return 1;
    else if(x<0)return -1;
    return 0;
}


double chebesh(double a, double b, double (*f)(double)) {
    return ((b - a) / 3.0) * (f((a + b) / 2.0 - (sqrt(2.0) / 4.0) * (b - a)) + f((a + b) / 2.0) + f((a + b) / 2.0 + (sqrt(2.0) / 4.0) * (b - a)));
}

double integral(double a, double b, double eps, double h, double functions(double)) {
	double sum = 0, i1, i2, delta, chi, mid, garant, x = a, count = 0;
	while (x < b) {
		i1 = chebesh(x, x + h, functions);
		i2 = chebesh(x, x + h/2.0, functions) + chebesh(x + h/2.0, x + h, functions);
		delta = (i2 - i1) / 15.0;
		if (x + h < b) {			
			garant += fabs(delta);
			mid += delta;	
		}
		

		if (fabs(delta) < eps) {
			if (x + h > b) { 
				h = b - x;
				i2 = chebesh(x, x + h/2.0, functions) + chebesh(x + h/2.0, x + h, functions);
	        	sum += i2;
                
                garant += fabs(delta);
			    mid += delta;
				break;
			}
			sum += i2;
	        x += h;
			count++;
	    }

		chi = pow(fabs(delta)/eps, 1.0/5.0);
		if (chi > 10) chi = 10;
		if (chi < 0.1) chi = 0.1;
		h = 0.95 * h / chi;
	}
	return sum;
}

double integral_equation(double *mas, double alfa, double eps) {
    double i1, i2, delta = 0, chi, x = 0, h = 0.1;
    int k = 0, count = 0;
    double mid = 0, garant = 0, sum = 0;

    while (1) { 
        i1 = chebesh(x, x + h, func);
        i2 = chebesh(x, x + h/2.0, func) + chebesh(x + h/2.0, x + h, func);
        delta = (i2 - i1) / 15.0;

        garant += fabs(delta);
        mid += delta;   

        if (fabs(delta) < eps) {

            if (sum + i2 > alfa) {
                double c[2], fa, fb, fc, a = x, b = x + h;
                int i = 0, ifa, ifb, ifc;

                c[0] = a;
                c[1] = b;
                
                fa = sum - alfa;
                fb = (sum + i2) - alfa; 

                ifa=sign(fa); ifb=sign(fb);
                if(ifa*ifb != -1) return 0;

                for(k = 0; fabs(c[1] - c[0]) > 1e-12; k++) {
                    i = !i;
                    c[i] = (a * fb - b * fa) / (fb - fa);

                    i2 = chebesh(x, (x + c[i])/2.0, func) + chebesh((x + c[i])/2.0, c[i], func);

                    fc = (sum + i2) - alfa;
                    
                    if (fabs(fc) < 1e-12) {

                        sum += i2;
                        delta = (i2 - i1) / 15.0;
                        garant += fabs(delta);
                        mid += delta;
            
                        mas[0] = sum;
                        mas[1] = garant;
                        mas[2] = mid;
                        mas[3] = count;
                        mas[4] = k;
                        return c[i];
                    }
                    ifc = sign(fc);

                    if(ifc*ifa==1){a=c[i]; fa=fc;}
                    else {b=c[i]; fb=fc;}
                }

            } else if (fabs(sum + i2 - alfa) < eps) {
                mas[0] = sum;
                mas[1] = garant;
                mas[2] = mid;
                mas[3] = count;
                mas[4] = k;
                return x;
            }

            sum += i2;
            x += h;
            count++;
        }

        chi = pow(fabs(delta)/eps, 1.0/5.0);
        if (chi > 10) chi = 10;
        if (chi < 0.1) chi = 0.1;
        h = 0.95 * h / chi;
        
    }
}

int main() {
    double alfa = 9, x, eps = 1e-7, sum7, sum9, sum11;
    double mas[5];
    double x_max = 0, x_min = 0;
    x = integral_equation(mas, alfa, 1e-11);
    
    x_max = x - (mas[0] - alfa + mas[1]) / func(x);
    x_min = x - (mas[0] - alfa - mas[1]) / func(x);
    printf("eps %le\n", eps);
    printf("x = %le garant = %le  mid = %le x_max = %le x_min = %le count = %g k = %g\n", x, mas[1], mas[2], x_max, x_min, mas[3], mas[4]);
    eps = 1e-9;
    x = integral_equation(mas, alfa, eps);
    
    printf("eps %le\n", eps);
    x_max = x - (mas[0] - alfa + mas[1]) / func(x);
    x_min = x - (mas[0] - alfa - mas[1]) / func(x);
    printf("x = %le garant = %le  mid = %le x_max = %le x_min = %le count = %g k = %g\n", x, mas[1], mas[2], x_max, x_min, mas[3], mas[4]);
    eps = 1e-11;
    x = integral_equation(mas, alfa, eps);
    sum7 = integral(0, x, 1e-7, 0.1, func);
    sum9 = integral(0, x, 1e-9, 0.1, func);
    sum11 = integral(0, x, eps, 0.1, func);
    printf("eps %le\n", eps);
    x_max = x - (mas[0] - alfa + mas[1]) / func(x);
    x_min = x - (mas[0] - alfa - mas[1]) / func(x);
    printf("x = %le garant = %le  mid = %le x_max = %le x_min = %le count = %g k = %g\n", x, mas[1], mas[2], x_max, x_min, mas[3], mas[4]);
    printf("Koef: %le", (sum7 - sum9) / (sum9 - sum11));
    return 0;
}