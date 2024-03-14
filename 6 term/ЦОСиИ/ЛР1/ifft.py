import numpy as np

def ifft(x):
    n = len(x)
    if n <= 1:
        return x
    even = ifft(x[0::2])
    odd = ifft(x[1::2])
    w = [np.exp(2j * np.pi * k / n) for k in range(n // 2)]
    return [even[k] + w[k] * odd[k] for k in range(n // 2)] + [even[k] - w[k] * odd[k] for k in range(n // 2)]