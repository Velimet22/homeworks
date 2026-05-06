#include <stdio.h>
#include <math.h>

int y = 1;

double f(double x, int y) {
    return pow(x, y);
}

double chebesh(double a, double b, double (*f)(double, int)) {
    double result = ((b - a) / 3.0) * (f((a + b) / 2.0 - (sqrt(2.0) / 4.0) * (b - a), y) + f((a + b) / 2.0, y) + f((a + b) / 2.0 + (sqrt(2.0) / 4.0) * (b - a), y));
    return result;
}

double centre(double a, double b, double (*f)(double, int)) {
    double result = (b - a) * (f((a + b) / 2.0, y));
    return result;
}

int main() {
    printf("Чебышев\n");
    for (int i = 0; i <= 6; i++) {
        y = i;
        printf("%d : %le %le\n",i , chebesh(0, 1, f), ((1.0 / (1.0 + i)) - chebesh(0, 1, f))); // первое выражение в погрешности -- точное значение найденное формулой Ньютона-Лейбница для (0 ; 1)
    }
    printf("\nЦентральный\n");
    for (int i = 0; i <= 4; i++) {
        y = i;
        printf("%d : %le %le\n",i , centre(0, 1, f), ((1.0 / (1.0 + i)) - centre(0, 1, f)));
    }

    return 0;
}