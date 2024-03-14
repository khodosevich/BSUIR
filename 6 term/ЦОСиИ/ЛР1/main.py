import matplotlib.pyplot as plt
import numpy as np
import fft , ifft , own_math

def draw_plot():
    x = np.linspace(0, 2 * np.pi, 32)
    y = own_math.set_function(x)

    y_fft = fft.fft(y)
    y_ifft = ifft.ifft([el / 32 for el in y_fft])

    plt.figure(figsize=(12, 6))

    plt.subplot(2, 3, 1)
    plt.plot(x, y)
    plt.title('Original function')

    plt.subplot(2, 3, 2)
    plt.stem(range(32), np.real(y_fft))
    plt.title('Real part FFT')

    plt.subplot(2, 3, 3)
    plt.stem(range(32), np.imag(y_fft))
    plt.title('Imag part FFT')

    plt.subplot(2, 3, 4)
    plt.stem(range(32), own_math.mod(y_fft))
    plt.title('FFT')

    plt.subplot(2, 3, 5)
    plt.plot(range(32), np.real(y_ifft)) 
    plt.title('iFFT')

    x = np.linspace(0, 2 * np.pi, 32)
    y = own_math.set_function(x)

    y_lib_fft = np.fft.fft(y)
    y_lib_ifft = np.fft.ifft(y_lib_fft)

    plt.figure(figsize=(12, 6))

    plt.subplot(2, 3, 1)
    plt.plot(x, y)
    plt.title('Original function')

    plt.subplot(2, 3, 2)
    plt.stem(range(32), np.real(y_lib_fft))
    plt.title('Real part FFT lib')

    plt.subplot(2, 3, 3)
    plt.stem(range(32), np.imag(y_lib_fft))
    plt.title('Imag part FFT lib')

    plt.subplot(2, 3, 4)
    plt.stem(range(32), np.abs(y_lib_fft))
    plt.title('FFT lib')

    plt.subplot(2, 3, 5)
    plt.plot(range(32), np.real(y_lib_ifft))
    plt.title('iFFT lib')

    plt.tight_layout()
    plt.show()

def main ():
    draw_plot()

if __name__ == "__main__":
    main()