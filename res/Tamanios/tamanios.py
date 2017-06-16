#!/bin/python
# programa que levanta los datos de energia y magnetizacion y los plotea

import numpy as np
from matplotlib import pyplot as plt

energia8 = np.genfromtxt('energiaL8.txt', delimiter = '\t')
energia32 = np.genfromtxt('energiaL32.txt', delimiter = '\t')
energia64 = np.genfromtxt('energiaL64.txt', delimiter = '\t')
energia128 = np.genfromtxt('energiaL128.txt', delimiter = '\t')

magnet8 = np.genfromtxt('magnetizacionL8.txt', delimiter = '\t')
magnet32 = np.genfromtxt('magnetizacionL32.txt', delimiter = '\t')
magnet64 = np.genfromtxt('magnetizacionL64.txt', delimiter = '\t')
magnet128 = np.genfromtxt('magnetizacionL128.txt', delimiter = '\t')

T = np.linspace(0,5, len(energia8))

plt.plot(T[0:-1], energia8[0:-1], 'r.', label = 'L=8', ms = 5)
plt.plot(T[0:-1], energia32[0:-1], 'g^', label = 'L=32', ms = 5)
plt.plot(T[0:-1], energia64[0:-1], 'bx', label = 'L=64', ms = 5)
plt.plot(T[0:-1], energia128[0:-1], 'k*', label = 'L=128', ms = 5)

plt.legend(loc = 'best')
plt.title('Energía para distintos tamaños de red')
plt.ylabel('Energía por sitio')
plt.grid(True)
plt.xlabel('T')

plt.figure()
plt.plot(T[0:-1], magnet8[0:-1], 'r.', label = 'L=8', ms = 5)
plt.plot(T[0:-1], magnet32[0:-1], 'g^', label = 'L=32', ms = 5)
plt.plot(T[0:-1], magnet64[0:-1], 'bx', label = 'L=64', ms = 5)
plt.plot(T[0:-1], magnet128[0:-1], 'k*', label = 'L=128', ms = 5)

plt.legend(loc = 'best')
plt.title('Magnetización para distintos tamaños de red')
plt.ylabel('Magnetización por sitio')
plt.grid(True)
plt.xlabel('T')

plt.show()
