from PIL import Image
import os,sys
from bisect import bisect_left

txt = []
soln = []

def bsrch(i):
	global soln
	try:
		if(soln[bisect_left(soln,i)]==i): return True
		else: return False
	except:
		return False

mazeToSolve = str(sys.argv[1])
white = (255,255,255)
black = (0,0,0)
ansClr = (255,69,0)

for line in open(mazeToSolve):
    txt+=[line[:-1]]

print "Done reading maze"

s=''
if(len(sys.argv)<3):
	f=open("ans.txt",'r')
	for i in f:
    		s+=i
	f.close()
	print "Done reading answer file"
soln=[int(i) for i in s.split()]
soln=sorted(soln)

lenX = len(txt[0])
lenY = len(txt)
c=0
cc=0

img = Image.new( 'RGB', (lenX,lenY), "white") 
pixels = img.load() 
for j in range(img.size[1]):
    for i in range(img.size[0]):
        if(bsrch(c)):pixels[i,j] = ansClr
        elif(txt[j][i]!=' '):pixels[i,j] = black
        else: pixels[i,j] = white
        c+=1
        
        
img.save("ans.png",format="png")
