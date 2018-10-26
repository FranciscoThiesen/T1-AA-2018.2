from math import *
import numpy as np
import random

class Matrix:
    def __init__(self, N, low, high):
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
    










