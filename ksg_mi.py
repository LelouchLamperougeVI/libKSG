import numpy as np
from ctypes import *

def ksg_mi(x: np.ndarray, y: np.ndarray, k=5):
    ksg = CDLL('./libksg.so').ksg
    ksg.restype = c_double
    joint = np.array([x, y]).T.flatten()
    I = ksg(joint.ctypes.data_as(POINTER(c_double)), int(x.size/2), k)
    return I
