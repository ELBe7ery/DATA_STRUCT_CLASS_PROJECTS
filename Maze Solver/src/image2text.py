from PIL import Image
import os,sys


txt = []
soln = []

img = Image.open(str(sys.argv[1])) 
pxls = img.load()

xStart=0
xEnd=0

fileStr=[]
for j in range(2,img.size[1]-2):
    str1=""
    for i in range(2,img.size[0]-2):
        if(pxls[i,j]==0):
            str1+="#"
        else:
            str1+=" "
    fileStr+=[str1+"\n"]
    
    
f=open("i2t.txt",'w+')

for i in fileStr:
    f.write(i)
    
f.close()