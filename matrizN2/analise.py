import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def func(x, a, b, c):
    return a*(x ** 2) + b * x + c

def func2(x, a, b, c, d):
	return a * (x ** 3) + b * (x ** 2) + c * x + d

x = []
y = []
y2 = []
f = open("tempoMatMult.csv", "r")
fst = True
for line in f:
    string = line.split(',')
    if fst == False:
        x.append(float(string[0]))
        y.append(float(string[3]))
        y2.append(float(string[2]))
        print(string[0], string[3])
    else:
        fst = False

x = np.array(x)
y = np.array(y)
y2 = np.array(y2)


popt, pcov= curve_fit(func, x, y)
popt2, pcov = curve_fit(func2, x, y2)

plt.figure()
plt.xlabel("Tamanho da instancia (NxN) ")
plt.ylabel("Tempo de CPU(s)")
plt.title("Analise dos dois algoritmos em conjunto")
plt.plot(x, y, 'ko', label="experimentos - paper")
plt.plot(x, y2, 'ko', label="experimentos - pedestre")
plt.plot(x, func(x, *popt), '-', label="fit quadratico")
plt.plot(x, func2(x, *popt2), '-', label="fit cubico")
plt.legend()
plt.show()
