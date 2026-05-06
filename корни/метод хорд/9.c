#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

int nf; // число обращений к функции
int sign(double x) {
    if(x>0)return 1;
    else if(x<0)return -1;
    return 0;
}
double g(double x) {
    nf++;
    return x*x + pow(x - 1, 5);
}

int root_chords(double *x, double a, double b, double (*f)(double), double epsilon) {
    double fa,fb,fc,c[2];
    int i=0,ifa,ifb,ifc,k;

    c[0]=a; c[1]=b; fa=f(a); fb=f(b);

    // Проверка условий запуска итераций:
    if(fabs(fa)<epsilon){*x=a; return 1;}
    if(fabs(fb)<epsilon){*x=b; return 1;}
    ifa=sign(fa); ifb=sign(fb);
    if(ifa*ifb != -1) return 0;

    for(k=1; fabs(c[1]-c[0])>epsilon; k++) {
        // последовательное сохранение промежуточной точки
        i=!i;
        c[i]=(a*fb-b*fa)/(fb-fa);
        fc=f(c[i]); ifc=sign(fc);
        // если значение функции мало:
        if(fabs(fc)<epsilon){*x=c[i]; return k+1;}
        // выбор подотрезка [a,c] или [c,b] :
        if(ifc*ifa==1){a=c[i]; fa=fc;}
        else {b=c[i]; fb=fc;}
    }

    *x=c[i]; // возвращается последнее значение величины С
    return k; // возвращается число итераций
}
int main() {
    double x; int res;
    nf=0;
    res=root_chords(&x,0,2,g,1.e-15);
    if(res) {
        printf("x=%lg\nчисло итераций=%d\n",x,res-1);
        printf("число обращений к функции=%d\n",nf);
    }
    else {
        printf("метод не применим\n");
    }
    return 0;
}