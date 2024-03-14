import math
import numpy as np
def mod(x):
    return [math.sqrt(elem.real**2 + elem.imag**2) for elem in x]

def set_function(x):
    return np.cos(2 * x) + np.sin(5 * x)
