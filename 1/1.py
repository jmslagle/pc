#!/usr/bin/env python

import os
import sys

def doit(i,c):
    # print "Considering Case #%d: %s" % (i,c)
    out=0
    a={}
    n=0
    a[c[0]]=1
    y=c[1:]
    for x in y:
        if not a.has_key(x):
            a[x]=n
            n=len(a)
    # print a
    base=len(a)
    if (base==1): # No unarary, always have at least 2 symbols even if
        base=2    # only 1 is specifiec
    n=len(c)-1
    # print "Base %d" % base
    for x in c: # Second loop to do the actual addition
        out=out+((base**n)*(a[x]))
        # print x,n,a[x],((base**n)*(a[x]))
        n=n-1
    print "Case #%d: %d" % (i,out)


try:
    inf = sys.argv[1]

    f = open(inf,'r')
except:
    print "Error opening file %s" % inf
    sys.exit(-1)

ca=f.readline()

c=int(ca)

for i in range(1,c+1):
    cc=f.readline().strip()
    doit(i,cc)


    
