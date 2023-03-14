## full_step
import matplotlib.pyplot as plt
import numpy as np

sample = 400
x = np.arange(1, sample, 2)
y = np.loadtxt("/home/chad/Desktop/course/AVR/MCU/AVR_Atmega128/PWM/info/Data/step_precise")
plt.plot(x, y, label='steps-error-full')

## half_step
sample = 400
x = np.arange(sample)
y = np.loadtxt("/home/chad/Desktop/course/AVR/MCU/AVR_Atmega128/PWM/info/Data/step_precise_halfstep_1")
plt.plot(x, y, label='steps-error-half_1')

## half_step
sample = 400
x = np.arange(sample)
y = np.loadtxt("/home/chad/Desktop/course/AVR/MCU/AVR_Atmega128/PWM/info/Data/step_precise_halfstep_2")
plt.plot(x, y, label='steps-error-half_2')

plt.xlabel('sample(n)')
plt.ylabel('precise')
plt.xlim(-10,410)
plt.title('position_precise_error', fontsize=25)
plt.legend()
plt.show()