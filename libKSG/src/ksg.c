#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_sf_psi.h>

#include "ksg.h"

int comp (const void *a, const void *b) {
    if (*(double *) a > *(double *) b)
        return 1;
    if (*(double *) a < *(double *) b)
        return -1;
    return 0;
}

void zscore (double *x, size_t N) {
    for (int i = 0; i < 2; i++) {
        double mu = 0.0, std = 0.0;
        for (int j = 0; j < N; j++)
            mu += x[j*2 + i];
        mu /= N;
        for (int j = 0; j < N; j++) {
            x[j*2 + i] -= mu;
            std += pow(x[j*2 + i], 2);
        }
        std = sqrt(std / N);
        for (int j = 0; j < N; j++)
            x[j*2 + i] /= std;
    }
    return;
}

double *binarysearch (double *sorted, double *query, int N) {
    if (N < 2)
        return sorted;

    double *found;
    double comparison = *(sorted + N/2) - *query;
    if (comparison < 0)
        found = binarysearch(sorted + N/2 + 1, query, N/2 - !(N % 2));
    else if (comparison > 0)
        found = binarysearch(sorted, query, N/2);
    else
        return sorted + N/2;
    return found;
}

int search (double *sorted, double low, double high, size_t N) {
    double *base = binarysearch(sorted, &low, N);
    while (*base <= low)
        base++;
    double *top = binarysearch(sorted, &high, N);
    while (*top >= high)
        top--;
    if (top - base < 1)
        return 1;
    return top - base;
}

double ksg (double *x, size_t N, int k) {
    unique(x, N);

    size_t newN = 0;
    while (!isnan(x[newN*2]) && newN != N)
        newN++;
    N = newN;

    zscore(x, N);

    double *sortx = (double *) malloc(sizeof(double) * N);
    double *sorty = (double *) malloc(sizeof(double) * N);
    for (int i = 0; i < N; i++) {
        sortx[i] = x[i*2];
        sorty[i] = x[i*2 + 1];
    }
    qsort(sortx, N, sizeof(double), comp);

    node *tree = (node *) malloc(sizeof(node) * N);
    mktree(x, N, 0, tree);

    double **e = (double **) malloc(sizeof(double *) * N);
    eball(tree, x, e, N, k + 1);

    double I = 0.0, low, high, ex, ey;
    for (int i = 0; i < N; i++) {
        ex = fabs(x[i*2] - *e[i]);
        ey = fabs(x[i*2 + 1] - *(e[i] + 1));
        ex = (ex > ey) ? ex : ey;
        for (int j = 0; j < 2; j++) {
            high = x[i*2 + j] + ex;
            low = x[i*2 + j] - ex;
            if (!j)
                I += gsl_sf_psi_int(search(sortx, low, high, N));
            else
                I += gsl_sf_psi_int(search(sorty, low, high, N));
        }
    }
    I /= N;
    I = gsl_sf_psi_int(k) - I + gsl_sf_psi_int(N);
    I /= log(2); // to bits
    
    free(tree);
    free(e);
    free(sortx);
    free(sorty);

    return I;
}

