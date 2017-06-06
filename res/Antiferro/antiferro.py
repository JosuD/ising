#!/bin/python
# programa que levanta los datos de energia y magnetizacion y los plotea

import numpy as np
from matplotlib import pyplot as plt

energiaB1 = np.genfromtxt('energia_B1.txt', delimiter = '\t')
magnetB1 = np.genfromtxt('magnetizacion_B1.txt', delimiter = '\t')
energiaB01 = np.genfromtxt('energia_B01.txt', delimiter = '\t')
magnetB01 = np.genfromtxt('magnetizacion_B01.txt', delimiter = '\t')

T = np.linspace(0,5, len(energiaB1))

plt.plot(T, energiaB1, 'r^', label = 'B=1', ms = 5)
plt.plot(T, energiaB01, 'b.', label = 'B=0.1', ms = 5)
plt.title('Caso antiferromagnético (J=-1)')
plt.ylabel('Energia')
plt.grid(True)
plt.legend(loc = 'best')
plt.xlabel('T')

plt.figure()
plt.plot(T, magnetB1, 'r^', label = 'B=1', ms = 5)
plt.plot(T, magnetB01, 'b.', label = 'B=0.1', ms = 5)
plt.title('Caso antiferromagnético (J=-1)')
plt.ylabel('Magnetización')
plt.grid(True)
plt.legend(loc = 'best')
plt.xlabel('T')

plt.show()
