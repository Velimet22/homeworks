#include <stdio.h>
#include <math.h>

double my_cos(double x) {
    double sum=1.0, h, eps=1.e-16; int i=2;
    h=(-x*x)/2;

    do {
        sum+=h;
        h*=(-x*x)/(2*i);
        i++;
    }
    while(fabs(h) > eps);
    return sum;
}


int main() {
    double x = 1;
    while (1) {
        printf("%.1lf %lf %le %le\n", x, my_cos(x), cos(x) - my_cos(x), ((cos(x) - my_cos(x)) / cos(x)));
        x++;
    }
    
    return 0;
}