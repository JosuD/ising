#!/bin/python
# programa que levanta los datos de energia y magnetizacion y los plotea

import numpy as np
from matplotlib import pyplot as plt
#from matplotlib import rm

baja = np.loadtxt('t_baja.txt')
critica = np.loadtxt('t_critica.txt')
alta = np.loadtxt('t_alta.txt')

k = np.arange(len(baja))

plt.plot(k[0:9000], baja[0:9000], 'r.', label = 'T baja', ms = 5)
plt.plot(k[0:9000], critica[0:9000], 'b+', label = 'T critica', ms = 5)
plt.plot(k[0:9000], alta[0:9000], 'ko', label = 'T alta', ms = 5)
plt.title('Correlación a distintas T para red 32x32')
plt.grid(True)
plt.legend(loc = 'best')
plt.xlabel('k')
plt.ylabel(r'$\zeta$')
plt.show()
