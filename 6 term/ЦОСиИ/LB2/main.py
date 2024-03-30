import numpy as np
import matplotlib.pyplot as plt
import fft , ifft, function

sin = 1
cos = 4
n = 16

original_continuous_x1 = np.linspace(0, 2* np.pi, 100)
original_continuous_y1 = np.sin(sin * original_continuous_x1)

original_continuous_x2 = np.linspace(0, 2 * np.pi, 100)
original_continuous_y2 =  np.cos(cos * original_continuous_x2)

orginal_discrete_x1 = np.linspace(0, 2 * np.pi, n)
orginal_discrete_y1 = np.sin(sin * orginal_discrete_x1)

orginal_discrete_x2 = np.linspace(0, 2 * np.pi, n)
orginal_discrete_y2 = np.cos(cos * orginal_discrete_x2)

furie_y1 = fft.fft(orginal_discrete_y1)
furie_y2 = fft.fft(orginal_discrete_y2)

linear_convolutionMy = function.linear_convolution(orginal_discrete_y1, orginal_discrete_y2, n)
linear_convolutionLib = np.convolve(orginal_discrete_y1, orginal_discrete_y2, mode='full')

cyclicConvolutionMy = function.cyclic_convolution(orginal_discrete_y1, orginal_discrete_y2, n)

furie = ifft.ifft([furie_y1[k] * furie_y2[k] for k in range(n)])
furie = [el / 32 for el in furie]

correlation = function.correlation(orginal_discrete_y1, orginal_discrete_y2, n)
correlation_lib = np.correlate(orginal_discrete_y1, orginal_discrete_y2, mode='full')[:n][::-1]

plt.figure(figsize=(8, 8))

plt.subplot(7, 2, 1)
plt.plot(original_continuous_x1, original_continuous_y1)
plt.title('Оriginal function 1')

plt.subplot(7, 2, 2)
plt.plot(original_continuous_x2, original_continuous_y2)
plt.title('Оriginal function 2')

plt.subplot(5, 2, 3)
plt.stem(range(2 * n - 1), linear_convolutionMy)
plt.title('Linear convolution')

plt.subplot(5, 2, 4)
plt.stem(range(2 * n - 1), linear_convolutionLib)
plt.title('Linear convolution(Lib)')

plt.subplot(4, 2, 5)
plt.stem(range(n), cyclicConvolutionMy)
plt.title('Cyclic convolution')

plt.subplot(4, 2, 6)
plt.stem(range(n), furie)
plt.title('Convolution FFT')

plt.subplot(4, 2, 7)
plt.stem(range(n), correlation)
plt.title('Correlation')

plt.subplot(4, 2, 8)
plt.stem(range(n), correlation_lib)
plt.title('Correlation(Lib)')

plt.subplots_adjust(hspace=0.5)
plt.tight_layout()
plt.show()