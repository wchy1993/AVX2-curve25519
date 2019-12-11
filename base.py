b = 256
q = 2**255 - 19
l = 2**252 + 27742317777372353535851937790883648493

def expmod(b,e,m):
  if e == 0: return 1
  t = expmod(b,e/2,m)**2 % m
  if e & 1: t = (t*b) % m
  return t

def inv(x):
  return expmod(x,q-2,q)

d = -121665 * inv(121666)
I = expmod(2,(q-1)/4,q)

def xrecover(y):
  xx = (y*y-1) * inv(d*y*y+1)
  x = expmod(xx,(q+3)/8,q)
  if (x*x - xx) % q != 0: x = (x*I) % q
  if x % 2 != 0: x = q-x
  return x

By = 4 * inv(5)
Bx = xrecover(By)
B = [Bx % q,By % q]
#print(By)

def edwards(P,Q):
  x1 = P[0]
  y1 = P[1]
  x2 = Q[0]
  y2 = Q[1]
  x3 = (x1*y2+x2*y1) * inv(1+d*x1*x2*y1*y2)
  y3 = (y1*y2+x1*x2) * inv(1-d*x1*x2*y1*y2)
  return [x3 % q,y3 % q]



     
def radix255(x):
    bin = "{0:b}".format(x)
    a = [26, 25, 26, 25, 26, 25, 26, 25, 26, 25]
    base = x
    result = ""
    for  i in range(10):
        radix= bin[-a[i]:]
        base = base>>a[i]
        bin =  "{0:b}".format(base)
        #print(base)
        b =int(radix,2)
        if i==9:
            result = result + str(b)
        else:
            result = result+str(b)+","
    #result = result+str(b)
    #print(type(result))
    return  result

Bi = B
Badd = B
Bsub = B
Bmul = B


for i in range(8):
        print("{")
        Bij = Bi
	Badd = Bij
	Bsub = Bij
	Bmul = Bij
	for j in range(8):
		print " { "
                print " { "
		for i in range(4):
			print "  {",radix255((Badd[0]+Badd[1])%q),"},"
		    	for k in range(8):
		    		Badd = edwards(Badd,Badd)
                print "};"
                print " { "
		for i in range(4):
			print "  {",radix255((Bsub[1]-Bsub[0])%q),"},"
		    	for k in range(8):
		    		Bsub = edwards(Bsub,Bsub)
                print "};"
                print " { "
		for i in range(4):
			print "  {",radix255((2*d*Bmul[1]*Bmul[0])%q),"},"
		    	for k in range(8):
		    		Bmul = edwards(Bmul,Bmul)
                print "};"
		print " },"
		
	        Bij = edwards(Bij,Bi)
	        Badd = Bij
	        Bsub = Bij 
	        Bmul = Bij
	print("},")
	for k in range(32):
		Bi = edwards(Bi,Bi)


print(bin(q))

 


