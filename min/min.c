#include <stdio.h>
#include <math.h>

double func(double x) {
    return x / (1.0 + x*x);
}

int main() {
    double a = -2, b = 10;
    double x1, x2 = (a + b) / 2, x3;
    double f1, f2, f3;
    double eps = 1e-12;

    while ((fabs(b - a) > eps * fabs(a + b) / 2) || (fabs(b - a) > eps)) {
        x1 = (a + x2) / 2.0;
        x3 = (x2 + b) / 2.0;

        f1 = func(x1);
        f2 = func(x2);
        f3 = func(x3);

        if ((f1 < f2) && (f1 < f3)) {
            b = x2;
            x2 = x1;
        } else if ((f2 < f1) && (f2 < f3)) {
            a = x1;
            b = x3;
        } else {
            a = x2;
            x2 = x3;
        }
    }
    printf("%le", x2);

    return 0;
}