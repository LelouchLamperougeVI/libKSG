# libKSG

A performant implementation of the KSG mutual information estimator (first algorithm).
The algorithm is written in C with a Python wrapper provided for convenience.

Original publication:
```
Kraskov, A., Stögbauer, H., & Grassberger, P. (2004). Estimating mutual information. Physical Review E—Statistical, Nonlinear, and Soft Matter Physics, 69(6), 066138.
```
https://journals.aps.org/pre/abstract/10.1103/PhysRevE.69.066138

## Installation
The GNU Scientific Library is required for compilation, which comes shipped with most linux distros.

```SHELL
git clone https://github.com/LelouchLamperougeVI/libKSG.git
cd libKSG
make
make test
./test
```

## Usage
The main function takes a pointer ```x``` to an array of doubles of length ```N * 2```.
```C
double ksg(double *x, size_t N, int k)
```
The array is assumed to be a two-columns matrix presented in row-major form
(i.e. the first two entries correspond to the first elements on the two separate columns and so on).
The two columns represent the x/y coordinates of data points for a total of ```N``` points.
```k``` is the k-th nearest neighbour, as described in the publication.

> **NOTE:** Mutual information may be returned as negative.

### Python
The following Python wrapper is provided:
```Python
ksg_mi(x: np.ndarray, y: np.ndarray, k=5)
```
> Parameters:
> >  x, y:   input vectors
> >
> >  k:      nearest neighbour
>
> Returns:
> >  I:      mutual information
