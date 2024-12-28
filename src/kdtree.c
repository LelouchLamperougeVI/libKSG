#include <stdlib.h>
#include <float.h>
#include <math.h>

#include "ksg.h"

double *maxD;

void argmax (double *x, int n) {
    double *max = x;
    for (int i = 1; i < n; i++) {
        if (*max < x[i])
            max = x + i;
    }
    maxD = max;
    return;
}

void insert (double *dist, double **neighbours, double *x, double *y, int k) {
    double D = pow(*x - *y, 2) + pow(*(x + 1) - *(y + 1), 2);
    if (*maxD > D) {
        *maxD = D;
        neighbours[maxD - dist] = x;
        argmax(dist, k);
    }
    return;
}

node* mktree (double *x, size_t N, int col, node *root) {
    root->left = NULL;
    root->right = NULL;
    root->isleaf = 0;
    if (N == 1) {
        root->addr = x;
        root->isleaf = 1;
        return root + 1;
    }

    if (col)
        qsort(x, N, sizeof(double) * 2, compare_c2);
    else
        qsort(x, N, sizeof(double) * 2, compare_c1);

    double *split = x + (N / 2 - !(N % 2)) * 2;
    root->addr = split;

    col = !col;
    size_t subN;
    node *next = root + 1;

    subN = N / 2 - !(N % 2);
    if (subN > 0) {
        root->left = next;
        next->parent = root;
        next = mktree(x, subN, col, next);
    }

    subN = N / 2;
    if (subN > 0) {
        root->right = next;
        next->parent = root;
        next = mktree(split + 2, subN, col, next);
    }

    return next;
}

void knnsearch (node *root, double *query, double *dist, double **neighbours, int k, int col) {
    double D;
    node *previous, *next = root;

    while (1) {
        insert(dist, neighbours, next->addr, query, k);
        if (next->isleaf)
            break;

        if (next->left == NULL)
            next = next->right;
        else if (next->right == NULL)
            next = next->left;
        else if (*(next->addr + col) < *(query + col))
            next = next->right;
        else
            next = next->left;

        col = !col;
    }

    while (1) {
        previous = next;
        next = next->parent;
        if (next == root->parent || next == NULL)
            break;

        col = !col;
        D = *(next->addr + col) - *(query + col);

        if (fabs(D) <= sqrt(*maxD)) {
            if (previous == next->right && next->left != NULL)
                knnsearch(next->left, query, dist, neighbours, k, (col + 1) % 2);
            else if (previous == next->left && next->right != NULL)
                knnsearch(next->right, query, dist, neighbours, k, (col + 1) % 2);
        }
    }

    return;
}

void eball (node *tree, double *points, double **e, int N, int k) {
    double *dist = (double *) malloc(sizeof(double) * k);
    double **neighbours = (double **) malloc(sizeof(double *) * k);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < k; j++)
            dist[j] = DBL_MAX;
        maxD = dist;
        knnsearch(tree, points + i*2, dist, neighbours, k, 0);
        e[i] = neighbours[maxD - dist];
    }

    free(dist);
    free(neighbours);
    return;
}
