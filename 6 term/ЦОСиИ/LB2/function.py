def linear_convolution(signal_1, signal_2, n):
    signal_3 = [0] * (2 * n - 1)
    for i in range(2 * n - 1):
        sum = 0
        for j in range(n):
            if i - j < 0:
                break
            if i - j > (n - 1):
                continue
            sum += signal_1[j] * signal_2[i - j]
        signal_3[i] = sum
    return signal_3

def cyclic_convolution(signal_1, signal_2, n):
    signal_3 = [0] * n
    for i in range(n):
        sum = 0
        for j in range(n):
            index = (i - j) % n
            sum += signal_1[j] * signal_2[index]
        signal_3[i] = sum
    return signal_3

def correlation(signal_1, signal_2, n):
    signal_3 = [0] * n
    for i in range(n):
        sum = 0
        for j in range(n):
            if i + j >= n:
                continue
            sum += signal_1[j] * signal_2[i + j]
        signal_3[i] = sum
    return signal_3