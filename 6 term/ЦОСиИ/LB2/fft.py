import numpy as np

def fft(x):
    l = len(x)

    # step 1
    if l <= 1:
        return x

    # step 2
    even = fft(x[0::2])
    odd = fft(x[1::2])

    # step 3
    w = [np.exp(-2j * np.pi * k / l) for k in range(l // 2)]

    # step 4
    return [even[k] + w[k] * odd[k] for k in range(l // 2)] + [even[k] - w[k] * odd[k] for k in range(l // 2)]
