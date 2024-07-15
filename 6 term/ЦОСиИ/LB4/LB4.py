import numpy as np
import matplotlib.pyplot as plt
import pywt
from PIL import Image

def haar_wavelet_transform(signal, level):
    coeffs = []
    for _ in range(level):
        length = len(signal)
        if length == 1:
            coeffs.append(signal)
            break

        half_length = length // 2
        low_pass = np.zeros(half_length)
        high_pass = np.zeros(half_length)

        for i in range(half_length):
            low_pass[i] = (signal[2 * i] + signal[2 * i + 1]) / np.sqrt(2)
            high_pass[i] = (signal[2 * i] - signal[2 * i + 1]) / np.sqrt(2)

        coeffs.append(high_pass)
        signal = low_pass

    coeffs.append(signal)
    coeffs.reverse()
    print("Коэффициенты вейвлет-преобразования:")
    print(coeffs)
    return coeffs


def inverse_haar_wavelet_transform(coeffs):
    if not isinstance(coeffs, list):
        raise ValueError("Coefficients must be provided as a list")

    level = len(coeffs) - 1

    signal = coeffs[0]
    for i in range(1, level + 1):
        length = len(coeffs[i])
        reconstructed_signal = np.zeros(length * 2)
        for j in range(length):
            reconstructed_signal[2 * j] = (signal[j] + coeffs[i][j]) / np.sqrt(2)
            reconstructed_signal[2 * j + 1] = (signal[j] - coeffs[i][j]) / np.sqrt(2)
        signal = reconstructed_signal
    print("Восстановленная функция:")
    print(signal)
    return signal


N = 16
period = 2 * np.pi
X = np.linspace(0, period, N)

Y = np.cos(X) + np.sin(3 * X)
print("Исходная функция:")
print(Y)
level = int(np.log2(N))

coeffs = haar_wavelet_transform(Y, level)
reconstructed_signal = inverse_haar_wavelet_transform(coeffs)

coeffs_lib = pywt.wavedec(Y, 'haar', level=int(np.log2(N)))
reconstructed_signal_lib = pywt.waverec(coeffs_lib, 'haar')

fig, ((ax1, ax4), (ax2, ax5), (ax3, ax6)) = plt.subplots(3, 2, figsize=(12, 12))

ax1.set_title('Исходная функция y = cos(x) + sin(3*x)')
ax1.plot(X, Y, 'c')
ax1.grid()

ax2.set_title('Сигнал после БВП (уровни)')
for i, coeff in enumerate(coeffs):
    ax2.plot(X[:len(coeff)], coeff, label=f'Level {i + 1}')
ax2.legend()
ax2.grid()

ax3.set_title('Восстановленный сигнал')
ax3.plot(X, reconstructed_signal, 'c')
ax3.grid()

ax4.set_title('Исходная функция y = cos(x) + sin(3*x)')
ax4.plot(X, Y, 'c')
ax4.grid()

ax5.set_title('Сигнал после БВП (уровни) (lib)')
for i, coeff_lib in enumerate(coeffs_lib):
    ax5.plot(X[:len(coeff_lib)], coeff_lib, label=f'Level {i + 1}')
ax5.legend()
ax5.grid()

ax6.set_title('Восстановленный сигнал (lib)')
ax6.plot(X, reconstructed_signal_lib, 'c')
ax6.grid()

plt.tight_layout()
plt.savefig("graf.png")
plt.close(fig)
lib_img = Image.open("graf.png")

