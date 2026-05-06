#include <stdio.h>
#include <math.h>

double my_exp(double x) {
    double sum=1.0, h, eps=1.e-16; int i=2;
    h=fabs(x);

    do {
        sum+=h;
        h*=fabs(x)/i;
        i++;
    }
    while( fabs(h)>eps );
    if (x < 0) return 1.0/sum;
    else return sum;
}


int main() {
    printf("%lg %le %le\n", my_exp(1), exp(1) - my_exp(1), ((exp(1) - my_exp(1)) / exp(1)));
    printf("%lg %le %le\n", my_exp(10), exp(10) - my_exp(10), ((exp(10) - my_exp(10)) / exp(10)));
    printf("%lg %le %le\n", my_exp(40), exp(40) - my_exp(40), ((exp(40) - my_exp(40)) / exp(40)));
    printf("%lg %le %le\n", my_exp(50), exp(50) - my_exp(50), ((exp(50) - my_exp(50)) / exp(50)));
    printf("%lg %le %le\n", my_exp(-1), exp(-1) - my_exp(-1), ((exp(-1) - my_exp(-1)) / exp(-1)));
    printf("%lg %le %le\n", my_exp(-10), exp(-10) - my_exp(-10), ((exp(-10) - my_exp(-10)) / exp(-10)));
    printf("%lg %le %le\n", my_exp(-40), exp(-40) - my_exp(-40), ((exp(-40) - my_exp(-40)) / exp(-40)));
    printf("%lg %le %le\n", my_exp(-50), exp(-50) - my_exp(-50), ((exp(-50) - my_exp(-50)) / exp(-50)));
    printf("%lg %le %le\n", my_exp(-65), exp(-65) - my_exp(-65), ((exp(-65) - my_exp(-65)) / exp(-65)));
    return 0;
}