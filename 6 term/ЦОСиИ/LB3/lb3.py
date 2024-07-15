import math
import numpy as np
import matplotlib.pyplot as plt


def Fft(inner):
    length = len(inner)
    out_list = []

    if length == 2:
        out_list.append(inner[0] + inner[1])
        out_list.append(inner[0] - inner[1])
    else:
        even = [inner[i] for i in range(0, length, 2)]
        odd = [inner[i] for i in range(1, length, 2)]

        result_even = Fft(even)
        result_odd = Fft(odd)

        out_list = [0] * length
        for i in range(length // 2):
            out_list[i] = result_even[i] + _w(i, length) * result_odd[i]
            out_list[i + length // 2] = result_even[i] - _w(i, length) * result_odd[i]

    return out_list

def Ifft(inner):
    length = len(inner)
    out_list = []

    if length == 2:
        out_list.append(inner[0] + inner[1])
        out_list.append(inner[0] - inner[1])
    else:
        even = [inner[i] for i in range(0, length, 2)]
        odd = [inner[i] for i in range(1, length, 2)]

        result_even = Ifft(even)
        result_odd = Ifft(odd)

        out_list = [0] * length
        for i in range(length // 2):
            out_list[i] = result_even[i] + np.conjugate(_w(i, length)) * result_odd[i]
            out_list[i + length // 2] = result_even[i] - np.conjugate(_w(i, length)) * result_odd[i]

    return out_list


def _w(n, n_total):
    return np.exp(-2j * np.pi * n / n_total)


def correlation_convolution_fft(first_sequence, second_sequence, operation):
    length = len(first_sequence)

    if length != len(second_sequence):
        raise ValueError("Sequences' lengths must be equal!")

    first_fft = np.fft.fft(first_sequence)
    second_fft = np.fft.fft(second_sequence)

    processed_first_fft = first_fft if operation == -1 else np.conjugate(first_fft)

    temp = np.zeros(length, dtype=complex)
    for i in range(length):
        temp[i] = processed_first_fft[i] * second_fft[i]

    result = np.fft.ifft(temp).real.tolist()

    return result


def hamming_window(total, n):
    return 0.54 + 0.46 * math.cos(2 * math.pi * n / (total - 1))

def low_pass_hamming_window_filter_func(noise_sequence, M, N):
    Fc = 0.05
    fft = Fft(noise_sequence)
    filter_arguments = np.zeros(N, dtype=complex)

    for i in range(N):
        window = hamming_window(M, i)
        temp = i - M / 2
        if temp == 0:
            filter_arguments[i] = Fc
        else:
            filter_arguments[i] = math.sin(2 * math.pi * Fc * temp) / (math.pi * temp)

        filter_arguments[i] *= window

    if np.sum(filter_arguments.real) == 0:
        raise ValueError("Sum of filter coefficients is zero.")

    result_filter_arguments = filter_arguments / np.sum(filter_arguments)

    return correlation_convolution_fft(fft, result_filter_arguments, -1)


def inner_function(x):
    return np.cos(2*x) + np.sin(5*x)

def noise(x):
    return np.sin(30 * x * np.pi) + np.cos(45 * x * np.pi)

def discretize(inner_function, n):
    return [inner_function(i * 2 * np.pi / n) for i in range(n)]

def draw_inner_function(inner_function, function_name):
    x = np.linspace(0, 2 * np.pi, 1000)
    y = np.real([inner_function(xi) for xi in x])

    plt.figure()
    plt.plot(x, y)
    plt.savefig(f"{function_name}.png")

def draw_real(samples_data, path):
    real_data = np.real(samples_data)
    plt.figure()
    plt.plot(real_data)
    plt.savefig(f"{path}.png")

def draw_magnitude(samples_data, path):
    magnitudes_data = np.abs(samples_data)
    plt.figure()
    plt.plot(magnitudes_data)
    plt.savefig(f"{path}.png")

def main():
    n = 64
    discrete_initial_func = discretize(inner_function, n)
    discrete_noise_func = discretize(noise, n)

    fft_initial = np.fft.fft(discrete_initial_func)
    fft_noise = np.fft.fft(discrete_noise_func)

    noise_sequence = np.add(discrete_initial_func, discrete_noise_func)

    fft_noise_sequence = np.fft.fft(noise_sequence)

    filtered_signal = low_pass_hamming_window_filter_func(fft_noise_sequence, 19, 64)

    fft_filtered = np.fft.fft(filtered_signal)

    draw_inner_function(inner_function, "1. Исходный")
    draw_inner_function(noise, "2. Шумы")

    draw_magnitude(fft_initial, "5. АЧХ исходный")
    draw_magnitude(fft_noise, "6. АЧХ шумы")
    draw_magnitude(fft_noise_sequence, "7. АЧХ шум + график")
    draw_magnitude(fft_filtered, "8. АЧХ после фильтр")

    draw_real(noise_sequence, "3. шум + график")
    draw_real(np.real(filtered_signal), "4. после фильтр")

if __name__ == "__main__":
    main()


