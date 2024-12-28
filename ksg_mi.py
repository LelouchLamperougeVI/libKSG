import numpy as np
from ctypes import *

def ksg_mi(x: np.ndarray, y: np.ndarray, k=5):
    ksg = CDLL('./libksg.so').ksg
    ksg.restype = c_double
    joint = np.hstack((x, y))
    joint = joint.flatten()
    I = ksg(joint.ctypes.data_as(POINTER(c_double)), int(x.size/2), k)
    return I
