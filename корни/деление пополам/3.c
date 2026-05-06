#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>

int nf;
int sign(double x) {
    if(x>0)return 1;
    else if(x<0)return -1;
    return 0;
}
double g(double x) {
    nf++;
    return cos(x) - x;
}

int root_chords(double *x, double a, double b, double (*f)(double), double epsilon) {
    double fa,fb,fc,c;
    int ifa,ifb,ifc,k;

    fa=f(a); fb=f(b);

    
    if(fabs(fa)<epsilon){*x=a; return 1;}
    if(fabs(fb)<epsilon){*x=b; return 1;}
    ifa=sign(fa); ifb=sign(fb);
    if(ifa*ifb != -1) return 0;

    for(k=1; fabs(b-a)>(epsilon*(fabs(a+b)/2)) && fabs(b-a)>epsilon; k++) {
        
        c = (a + b) / 2;
        fc=f(c); ifc=sign(fc);
        
        if(fabs(fc)<epsilon){*x=c; return k+1;}
        
        if(ifc*ifa==1){a=c; fa=fc;}
        else {b=c; fb=fc;}
    }

    *x=c; 
    return k; 
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