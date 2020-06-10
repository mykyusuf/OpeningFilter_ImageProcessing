import io
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

matrix=[]

with open('output.txt','r') as f:
    for line in f:
        xs = []
        for word in line.split():
            if(int(word)==0):
                xs.append(255)
            else:
                xs.append(0)
        matrix.append(xs)

plt.imshow(matrix,  )
plt.savefig("result.png")
