#!/bin/python
# programa que levanta los datos de energia y magnetizacion y los plotea

import numpy as np
from matplotlib import pyplot as plt

energiaanti = np.genfromtxt('energiaantiferro.txt', delimiter = '\t')
magnetanti = np.genfromtxt('magnetizacionantiferro.txt', delimiter = '\t')
energia = np.genfromtxt('energiaferro.txt', delimiter = '\t')
magnet = np.genfromtxt('magnetizacionferro.txt', delimiter = '\t')

T = np.linspace(0,5, len(energia))

plt.plot(T, energia, 'r^', label = 'J=1', ms = 5)
plt.plot(T, energiaanti, 'b.', label = 'J=-1', ms = 5)
plt.title('Caso antiferromagnético (J=-1)')
plt.ylabel('Energia')
plt.grid(True)
plt.legend(loc = 'best')
plt.xlabel('T')

plt.figure()
#plt.plot(T, magnet, 'r^', label = 'J=1', ms = 5)
plt.plot(T[0:-1], magnetanti[0:-1], 'b.', label = 'J=-1', ms = 5)
plt.title('Caso antiferromagnético (J=-1)')
plt.ylabel('Magnetización')
plt.grid(True)
#plt.legend(loc = 'best')
plt.xlabel('T')

plt.show()
