#!/bin/python
# programa que levanta los datos de energia y magnetizacion y los plotea

import numpy as np
from matplotlib import pyplot as plt

energiaJ1 = np.genfromtxt('energia_J1.txt', delimiter = '\t')
energiaJ01 = np.genfromtxt('energia_J01.txt', delimiter = '\t')
energiaJ03 = np.genfromtxt('energia_J03.txt', delimiter = '\t')
energiaJ06 = np.genfromtxt('energia_J06.txt', delimiter = '\t')
energiaJ15 = np.genfromtxt('energia_J15.txt', delimiter = '\t')

magnetJ1 = np.genfromtxt('magnetizacion_J1.txt', delimiter = '\t')
magnetJ01 = np.genfromtxt('magnetizacion_J01.txt', delimiter = '\t')
magnetJ03 = np.genfromtxt('magnetizacion_J03.txt', delimiter = '\t')
magnetJ06 = np.genfromtxt('magnetizacion_J06.txt', delimiter = '\t')
magnetJ15 = np.genfromtxt('magnetizacion_J15.txt', delimiter = '\t')

T = np.linspace(0,5, len(energiaJ1))

plt.plot(T[0:-1], energiaJ1[0:-1], 'r.', label = 'J=1', ms = 5)
plt.plot(T[0:-1], energiaJ01[0:-1], 'g^', label = 'J=0.1', ms = 5)
plt.plot(T[0:-1], energiaJ03[0:-1], 'bx', label = 'J=0.3', ms = 5)
plt.plot(T[0:-1], energiaJ06[0:-1], 'k*', label = 'J=0.6', ms = 5)
plt.plot(T[0:-1], energiaJ15[0:-1], 'ro', label = 'J=1.5', ms = 5)
plt.legend(loc = 'best')
plt.title('Energía para distintos grados de interacción')
plt.ylabel('Energía por sitio')
plt.grid(True)
plt.xlabel('T')

plt.figure()
plt.plot(T[0:-1], magnetJ1[0:-1], 'r.', label = 'J=1', ms = 5)
plt.plot(T[0:-1], magnetJ01[0:-1], 'g^', label = 'J=0.1', ms = 5)
plt.plot(T[0:-1], magnetJ03[0:-1], 'bx', label = 'J=0.3', ms = 5)
plt.plot(T[0:-1], magnetJ06[0:-1], 'k*', label = 'J=0.6', ms = 5)
plt.plot(T[0:-1], magnetJ15[0:-1], 'ro', label = 'J=1.5', ms = 5)
plt.legend(loc = 'best')
plt.title('Magnetización para distintos grados de interacción')
plt.ylabel('Magnetización por sitio')
plt.grid(True)
plt.xlabel('T')

plt.show()
