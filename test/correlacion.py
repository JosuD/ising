#!/bin/python
# programa que levanta los datos de energia y magnetizacion y los plotea

import numpy as np
from matplotlib import pyplot as plt

data = np.genfromtxt('magnet_corr.txt')

x_m2 = np.mean(data)**2
x2_m = np.mean(data**2)
x_ik = np.zeros(len(data))
for k in range(len(data)):
    tope = len(data)-k
    for i in range(tope):
        x_ik[k] += data[i]*data[i+k]/float(tope)
corr = (x_ik - x_m2)/(x2_m - x_m2)
k = np.arange(len(corr))

#plt.plot(k, corr, 'r.', label = 'datos', ms = 5)
#plt.title('correlacion')
#plt.grid(True)
#plt.xlabel('k')

plt.show()

np.savetxt('t_alta.txt', corr)
