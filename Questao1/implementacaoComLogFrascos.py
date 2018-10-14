from math import *
import time
import csv

def solveUsingLogBottles(maxBits, ans):
    #print("vamos resolver para bits = {}, ans = {}".format(maxBits, ans) ) 
    lo = 1
    hi = (1 << maxBits) - 1
    while lo < hi:
        mid = (int) (lo + hi) // 2
        if mid == ans:
            break
        elif mid < ans:
            lo = mid + 1
        else:
            hi = mid

pathInputPrefix = 'instancias/bignum_'
pathOutput = 'tempos/usandoLogFrascos.csv'

csvfile = open(pathOutput, 'w')
fieldnames = ['Tamanho da entrada', 'Tempo de CPU ( para as 50 instancias )']
writer = csv.DictWriter(csvfile, fieldnames = fieldnames)
writer.writeheader()

tamanhos = [32, 64, 128, 192, 256]

for numBits in tamanhos:
    for x in range(1, 3):    
        pathInputSuffix = str(numBits) + '_0' + str(x) + '.dat'
        # vamos ler o arquivo com os casos de teste
        arquivo = open(pathInputPrefix + pathInputSuffix, 'r')
        szBits = 0
        numTestes = 0
        vetorDeInstancias = []
        for line in arquivo:
            palavras = line.split()
            if len(palavras) == 1:
                vetorDeInstancias.append( int(palavras[0], 2) )
        arquivo.close()
        start = time.time()
        for instancia in vetorDeInstancias:
            solveUsingLogBottles(numBits, instancia)
        end = time.time()
        writer.writerow({'Tamanho da entrada' : str(numBits), 'Tempo de CPU ( para as 50 instancias )' : str(end - start) } )
csvfile.close()


