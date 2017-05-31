#!/bin/python
# programa que levanta los datos de energia y magnetizacion y los plotea

import numpy as np
from matplotlib import pyplot as plt
import os

print('Estoy en...\n')
os.system('pwd')
print('\n')
print('Me mudo a... \n')
os.chdir('/home/josue/Escritorio/ising/test')
#	  'cd ~/Escritorio/ising/bin'
os.system('pwd')
print('\n')

energia = np.genfromtxt('energia.txt', delimiter = '\t')
magnet = np.genfromtxt('magnetizacion.txt', delimiter = '\t')

#T = np.arange(len(energia))
T = np.linspace(0,5, len(energia))

plt.plot(T, energia, 'r.', label = 'datos', ms = 5)
plt.title('energia.txt')
plt.grid(True)
plt.xlabel('T')

plt.figure()
plt.plot(T, magnet, 'b.', label = 'datos', ms = 5)
plt.title('magnetizacion.txt')
plt.grid(True)
plt.xlabel('T')

plt.show()
