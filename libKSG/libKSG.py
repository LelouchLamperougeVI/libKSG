import numpy as np
import ctypes
import os
from pathlib import Path

class KSG:
    def __init__(self):
        path = os.path.dirname(os.path.abspath(__file__))
        path = os.path.abspath(os.path.join(path, os.pardir))
        lib = [p for p in Path(path).glob('cksg.cpython*.so')]
        self.lib = ctypes.CDLL(lib[0]).ksg
        self.lib.restype = ctypes.c_double

    def mi(self, x: np.ndarray, y: np.ndarray, k: int = 5, axis: int = 0, keepdims: bool = False):
        assert k > 0, 'k must be a positive integer'
        x = np.moveaxis(x, axis, 0)
        y = np.moveaxis(y, axis, 0)

        if x.ndim == 1:
            x = x[np.newaxis, :]
        if y.ndim == 1:
            y = y[np.newaxis, :]

        x = x.reshape(x.shape[0], -1)
        y = y.reshape(y.shape[0], -1)
        assert x.shape[1] == y.shape[1], 'x and y must have the same length'

        n = x.shape[1]
        I = np.empty((x.shape[0], y.shape[0]))
        for i, xx in enumerate(x):
            for j, yy in enumerate(y):
                joint = np.array([xx, yy]).T.flatten()
                I[i, j] = self.lib(joint.ctypes.data_as(ctypes.POINTER(ctypes.c_double)), n, k)

        if keepdims:
            return I
        return np.squeeze(I)
