import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def func(x, a, b):
    return a*x + b


x = []
y = []
f = open("usandoLogFrascos.csv", "r")
fst = True
for line in f:
    string = line.split(',')
    if fst == False:
        x.append(float(string[0]))
        y.append(float(string[1]))
        print(string[0], string[1])
    else:
        fst = False

x = np.array(x)
y = np.array(y)

print(x)
print(y)

popt, pcov= curve_fit(func, x, y)

plt.figure()
plt.xlabel("Tamanho da instancia (bits) ")
plt.ylabel("Tempo de CPU(s) -> 50 instancias")
plt.title("Analise dos tempos para log Frascos")
plt.plot(x, y, 'ko', label="experimentos")
plt.plot(x, func(x, *popt), '-', label="fit linear")
plt.legend()
plt.show()
