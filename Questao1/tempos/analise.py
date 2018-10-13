import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

def fit_func(x, a, b, c):
    return a * np.exp(-b * x) + c

def func(x, a, b):
    return a*x + b


x = []
y = []
f = open("usando16Frascos01.csv", "r")
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
y = np.array(np.log(y))

print(x)
print(y)

popt, pcov= curve_fit(func, x, y)

plt.figure()
plt.plot(x, y, 'ko', label="original")
plt.plot(x, func(x, *popt), '-', label="fit")
plt.legend()
plt.show()
