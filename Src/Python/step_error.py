import matplotlib.pyplot as plt
import numpy as np


sample = 200
x = np.arange(sample)
y = np.loadtxt("/home/chad/Desktop/course/AVR/MCU/AVR_Atmega128/PWM/info/Data/step_precise")
plt.plot(x, y, label='steps-error-firsr')
x = np.arange(sample)
y = np.loadtxt("/home/chad/Desktop/course/AVR/MCU/AVR_Atmega128/PWM/info/Data/step_precise_2")
plt.plot(x, y,label='steps-error-seconde')
x = np.arange(sample)
y = np.loadtxt("/home/chad/Desktop/course/AVR/MCU/AVR_Atmega128/PWM/info/Data/step_precise_3")
plt.plot(x, y,label='steps-error-seconde')
plt.xlabel('sample(n)')
plt.ylabel('precise')
plt.title('position_precise_error', fontsize=25)
plt.legend()
plt.show()
