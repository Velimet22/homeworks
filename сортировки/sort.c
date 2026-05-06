#include <stdio.h>
#include <stdlib.h>

void q_sort(int *mas, int left, int right) {
    int j, i, c, p;

    if (left < right) {
        i = left;
        j = right;
        p = mas[(i+j)/2];
    
        while(i<=j) {
            while(mas[i] < p) {i++;}
            while(mas[j] > p) {j--;}
            if (i <= j) {
                if (i < j) {
                    c = mas[i];
                    mas[i] = mas[j];
                    mas[j] = c;
                }
                i++;
                j--;
            }
        }
        q_sort(mas, left, j);
        q_sort(mas, i, right);
    }
}

int main(void) {
    int n, i;
    FILE *fin=NULL;
    int *mas = NULL;

    fin = fopen("input.txt", "r");
    if (!fin) return -1;
    
    if (fscanf(fin, "%d", &n) != 1) return -2;

    mas = (int*)malloc(n*sizeof(int));
    if (!mas) return -3;

    for (i = 0; i < n; i++) {
        if (fscanf(fin, "%d", &mas[i]) != 1) {
            break;
        }
    }

    q_sort(mas, 0, n-1);

    for (int j = 0; j < n; j++) {
        printf("%d ", mas[j]);
    }

    return 0;
}
