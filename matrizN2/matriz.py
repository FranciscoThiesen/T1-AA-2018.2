from math import *
from timeit import default_timer as timer
import numpy as np
import random
import csv
class Matrix:
    def __init__(self, N, low = 0, high = 1):
        self.N = N
        self.Mat = [ [0] * N for x in range(N) ]
        self.low = low
        self.high = high

    def fillRandom(self):
        for x in range(self.N):
            for y in range(self.N):
                self.Mat[x][y] = random.randint(self.low, self.high)

    def printMat(self):
        for x in range(self.N):
            for y in range(self.N):
                print(self.Mat[x][y], end = ' ')
            print()
    

def slowProd(M1, M2):
    if M1.N != M2.N:
        print("Invalid parameters for matrix multiplication")
        return -1
    dim = M1.N
    result = Matrix(dim)
    for i in range(dim):
        for j in range(dim):
            for k in range(dim):
                result.Mat[i][j] += (M1.Mat[i][k] * M2.Mat[k][j])
    return result


def fastProd(M1, M2):
    if M1.N != M2.N:
        print("Invalid parameters for matrix multiplication")
        return -1
    dim = M1.N
    a = 0
    b = 0
    for i in range(dim):
        a = max(a, max(M1.Mat[i]) )
        b = max(b, max(M2.Mat[i]) )
    
    x = dim * a * b + 1
    B = [0] * dim
    
    # calculate each b[i] using horner's method
    for k in range(dim):
        xPot = 1
        for j in range(dim):
            B[k] += (M2.Mat[k][j] * xPot)
            xPot *= x

    C = [0] * dim
    for i in range(dim):
        for k in range(dim):
            C[i] += (M1.Mat[i][k] * B[k])

    c = Matrix(dim)
    q = Matrix(dim)

    for i in range(dim):
        q.Mat[i][0] = C[i] // x
        c.Mat[i][0] = C[i] % x

        for j in range(1, dim - 2):
            q.Mat[i][j] = q.Mat[i][j - 1] // x
            c.Mat[i][j] = q.Mat[i][j - 1] % x
        
        c.Mat[i][ dim - 1] = q.Mat[i][dim - 3] // x
        c.Mat[i][ dim - 2] = q.Mat[i][dim - 3] % x
    
    
    return c


def genTest(N, low = 0, high = 1):
    M1 = Matrix(N, low, high)
    M2 = Matrix(N, low, high)
    # vamos fazer a multiplicacao n^3 para checar a corretude
    start = timer()
    M3 = slowProd(M1, M2)
    end = timer()
    tempoSlow = end - start
    start = timer()
    M4 = fastProd(M1, M2)
    end = timer()
    tempoFast = end - start
    tempoSlow = str(tempoSlow)
    tempoFast = str(tempoFast)
    return [tempoSlow, tempoFast]

outputfile = 'tempoMatMult.csv'
csvfile = open(outputfile, 'w')
fieldnames = ['Dimensao das Matrizes', 'Valor maximo permitido', 'Tempo pedestre', 'Tempo artigo']
writer = csv.DictWriter(csvfile, fieldnames = fieldnames)
writer.writeheader()

tamanhosDeTeste = [50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
valorMaximoDeMatriz = [1, 10, 100, 1000]

for tam in tamanhosDeTeste:
    dim = str(tam) + 'x' + str(tam)
    for val in valorMaximoDeMatriz:
        ret = genTest(tam, 0, val)
        writer.writerow({'Dimensao das Matrizes' : dim, 'Valor maximo permitido' : str(val), 'Tempo pedestre' : ret[0], 'Tempo artigo' : ret[1]})

csvfile.close()
