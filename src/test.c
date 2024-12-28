#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ksg.h"

int main () {
    printf("KSG estimator library - tester program\nAll tests conducted with k=5.\n© 2025 HaoRan Chang\n\n");

    int n = 2000, bign = 200000;
    double test[n], *big, I;
    FILE *file;

    file = fopen("data/rand.txt", "r");
    if (file == NULL) {
        perror("fopen()");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++)
        fscanf(file, "%lf\n", test + i);
    fclose(file);
    I = ksg(test, n/2, 5);
    printf("---RANDOM---\nmutual information:\t%f\n", I);


    file = fopen("data/flat.txt", "r");
    if (file == NULL) {
        perror("fopen()");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++)
        fscanf(file, "%lf\n", test + i);
    fclose(file);
    I = ksg(test, n/2, 5);
    printf("---FLAT LINE---\nmutual information:\t%f\n", I);


    file = fopen("data/positive.txt", "r");
    if (file == NULL) {
        perror("fopen()");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++)
        fscanf(file, "%lf\n", test + i);
    fclose(file);
    I = ksg(test, n/2, 5);
    printf("---POSITIVE LINE---\nmutual information:\t%f\n", I);


    file = fopen("data/donut.txt", "r");
    if (file == NULL) {
        perror("fopen()");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < n; i++)
        fscanf(file, "%lf\n", test + i);
    fclose(file);
    I = ksg(test, n/2, 5);
    printf("---DONUT---\nmutual information:\t%f\n", I);


    big = (double *) malloc(sizeof(double) * bign);
    file = fopen("data/bigrand.txt", "r");
    if (file == NULL) {
        perror("fopen()");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < bign; i++)
        fscanf(file, "%lf\n", big + i);
    fclose(file);
    printf("\nrunning a performance test with a million random values...\n");
    clock_t begin = clock();
    I = ksg(big, bign/2, 5);
    clock_t end = clock();
    printf("---BIG RANDOM---\nmutual information:\t%f\n", I);
    printf("took %f sec\n", (double) (end - begin) / CLOCKS_PER_SEC);
    free(big);

    return 0;
}
