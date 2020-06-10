import io
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt


file1 = open("structureElement.txt","w")
file1.close()
file1 = open("structureElement.txt","a")
image_string = open("structural.png", 'rb').read()
img = Image.open(io.BytesIO(image_string))
arr = np.asarray(img)
imgHeight=len(arr)
imgWidth=0
for i in arr:
    if(imgWidth<len(i)):
        imgWidth=len(i)
file1.write(str(imgHeight)+" "+str(imgWidth)+" 0 1")
file1.write("\n")
file1.write(str(int(imgHeight/2))+" "+str(int(imgWidth/2)))
file1.write("\n")

for i in arr:
    for j in i:
        if(j[0]==255):
            file1.write("0 ")
        else:
            file1.write("1 ")
    file1.write("\n")
file1.close()

file1 = open("imageB.txt","w")
file1.close()
file1 = open("imageB.txt","a")
image_string = open("image.png", 'rb').read()
img = Image.open(io.BytesIO(image_string))
arr = np.asarray(img)
imgHeight=len(arr)
imgWidth=0
for i in arr:
    if(imgWidth<len(i)):
        imgWidth=len(i)
file1.write(str(imgHeight)+" "+str(imgWidth)+" 0 1")
file1.write("\n")

a = np.zeros((imgHeight,imgWidth))

for i in arr:
    for j in i:
        if(j[0]==255):
            file1.write("0 ")
        else:
            file1.write("1 ")
    file1.write("\n")
file1.close()






