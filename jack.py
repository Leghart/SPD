#!/usr/bin/env python3

def czytaj_dane(nazwa):
    with open('inputs/JACK'+nazwa+'.DAT') as plik:
        linie=plik.readlines()

    ilosc=int(linie[0])+1
    dane =[]

    for x in linie:
        dane.append(x.strip())
    dane.pop(0)

    r=[0]
    p=[0]
    pom=0

    for x in dane:
        a,b=x.split()
        r.append(int(a))
        p.append(int(b))
    return r,p,ilosc

def jackson(r,p,ilosc):
    for i in range(ilosc-1):
        for j in range(1, ilosc):
            if r[j-1] > r[j]:
                r[j],r[j-1]=r[j-1],r[j]
                p[j],p[j-1]=p[j-1],p[j]

    C=[0]*(ilosc)
    for i in range(1,ilosc):
        C[i]=max(r[i],C[i-1])+p[i]
    print("Wynik: %d" %(C[ilosc-1]))
    return C

if __name__=='__main__':
    nazwa=input("Plik wejsciowy: ")
    r,p,ilosc=czytaj_dane(nazwa)
    C=jackson(r,p,ilosc)
