# libKSG

A performant implementation of the KSG mutual information estimator (first algorithm).
The algorithm is written in C and packaged in Python for convenience.
**Currently, only works on Linux 🙃**

![example output](example.png)

Original publication:
> Kraskov, A., Stögbauer, H., & Grassberger, P. (2004). Estimating mutual information. Physical Review E—Statistical, Nonlinear, and Soft Matter Physics, 69(6), 066138.

https://journals.aps.org/pre/abstract/10.1103/PhysRevE.69.066138

## Installation
The GNU Scientific Library is required for compilation, which comes shipped with most linux distros.
If you have trouble compiling, make sure that this library is installed using your distro's package manager.

### Python
Easiest way is to install the PyPI distribution with `pip`:
```SHELL
pip install libKSG
```
Or compile and install manually:
```SHELL
git clone https://github.com/LelouchLamperougeVI/libKSG.git
cd libKSG
pip install .
```

### C
If you only need the shared library, compile the C code:
```SHELL
git clone https://github.com/LelouchLamperougeVI/libKSG.git
cd libKSG
make
```
This will compile into a shared library `libksg.so`.
Additionally, you can compile and run the test programme to make sure everything works:
```SHELL
make test
./test
```

### MATLAB
_maybe in the future..._

## Usage
### Python
`libKSG` provides the class `KSG` with a single method `mi()`:
```python
libKSG.KSG.mi(x: np.ndarray, y: np.ndarray, k: int = 5, axis: int = 0, keepdims: bool = False)
```
##### Inputs:
x, y: _np.ndarray_\
&emsp;&emsp;Input vectors or matrices. The features must have the same lengths.

k: _int_\
&emsp;&emsp;Number of nearest neighbours (see publication).

axis: _int_\
&emsp;&emsp;Axis that contains individual features to be compared.\
&emsp;&emsp;All other axes will be flattened based on the 'C' ordering rule.

keepdims: _bool_\
&emsp;&emsp;Whether to keep the singleton dimensions.

##### Returns:
I: _np.ndarray_\
&emsp;&emsp;Matrix of shape _(x.shape[axis], y.shape[axis])_ containing mutual information values.\
&emsp;&emsp;If `keepdims == False`, singleton dimensions will be squeezed.

#### Example
```python
from libKSG import KSG # import the library
import numpy as np

n = 1_000;

theta = np.linspace(0, 2*np.pi, n) # generate test data
phi = np.random.randn(n) + 10
x = phi * np.cos(theta)
y = phi * np.sin(theta)

ksg = KSG() # create instance of KSG object
I = ksg.mi(x, y) # calculate mutual info between x and y

print(I)

```

### C
The main function takes a pointer ```x``` to an array of doubles of length ```N * 2```.
```C
double ksg(double *x, size_t N, int k)
```
The array is assumed to be a two-columns matrix presented in row-major form
(i.e. the first two entries correspond to the first elements on the two separate columns and so on).
The two columns represent the x/y coordinates of data points for a total of ```N``` points.
```k``` is the k-th nearest neighbour, as described in the publication.

> **NOTE:** Mutual information may be returned as negative.
