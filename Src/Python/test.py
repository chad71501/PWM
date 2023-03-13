import matplotlib.pyplot as plt
import numpy as np

Fs = 360
f = 1
sample = 360
x = np.arange(sample)
y = np.sin(2 * np.pi * f * x / Fs)+1
plt.plot(x, y)
plt.xlabel('sample(n)')
plt.ylabel('voltage(V)')