#ifndef KSG
#define KSG

typedef struct node {
    double *addr;
    struct node *left, *right, *parent;
    int isleaf;
} node;

int compare_c1 (const void *a, const void *b);

int compare_c2 (const void *a, const void *b);

node* mktree (double *x, size_t N, int col, node *root);

void knnsearch (node *root, double *query, double *dist, double **neighbours, int k, int col);

void eball(node *tree, double *points, double **e, int N, int k);

void unique (double *x, size_t N);

double ksg (double *x, size_t N, int k);

#endif
