#!/usr/bin/env python3
import random as ran
import datetime as time
import os
import matplotlib.pyplot as plt
import numpy as np

uchwyt="pomiary_czasu.txt"
zdj=("zobrazowanie_dzialania")
dane="dane.txt"
if os.path.isfile(dane):
    os.remove(dane)
if os.path.isfile(uchwyt):
    os.remove(uchwyt)
if os.path.isfile(zdj):
    os.remove(zdj)

def testuj(roz):
    tab_czas=[]*(5)
    tab_wynikow=[]*(5)
    for i in range(5):
        r,p,ilosc=czytaj_dane(roz)
        start=time.datetime.now()
        C=jackson(r,p,ilosc)
        wynik=time.datetime.now()-start
        tab_czas.append(wynik)
        tab_wynikow.append(C)

    plik=open("pomiary_czasu.txt","a")
    plik.write("Dla rozmiaru %s elementow" %(str(roz))+":"+"\n")
    for i in range(5):
        plik.write(str(tab_czas[i].microseconds)+'\n')

    plik=open("dane.txt","a")
    plik.write("Dla rozmiaru %s elementow" %(str(roz))+":"+"\n")
    for i in range(5):
        plik.write(str(tab_wynikow[i])+'\n')


def gen(roz):
    x=[]*(roz)
    x.append(str(roz)+"\n")
    for i in range(roz):
        r=ran.randint(1,100)
        p=ran.randint(1,100)
        x.append(str(r)+" "+str(p)+"\n")
    return x

def czyt(roz):
    with open('inputs/JACK2.DAT') as plik:
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

def czytaj_dane(roz):
    linie=gen(roz)
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
#    print("Wynik: %d" %(C[ilosc-1]))
    return C

def visualize(quantity, r, p, c):
    task_ysize = 5

    fig, ax = plt.subplots(2,1,figsize=(16,9))
    task_start_end = [0]*quantity
    for i in range(quantity):
        ax[0].broken_barh([(r[i], p[i])], (task_ysize*i+1, task_ysize-2))
        task_start_end[i] = r[i] + p[i]
    ax[0].set_xlabel('Dostepnosc zadan.')
    ax[0].set_yticks([i*task_ysize for i in range(1,quantity)])
    ax[0].set_yticklabels(['Zadanie {}'.format(i) for i in range(1,quantity)])
    ax[0].set_ylim(0, quantity*task_ysize)
    ax[0].set_xlim(0,)
    if max(task_start_end) <= 15:
        major_ticks = np.arange(0, max(task_start_end)+1, 1)
        ax[0].set_xticks(major_ticks)
        ax[0].grid(which='major', alpha=0.8)

    s = [0]*quantity
    for i in range(1, quantity):
        s[i] = max(r[i], c[i-1])
        ax[1].broken_barh([(s[i], p[i])], (task_ysize*i+1, task_ysize-2))
    ax[1].set_xlabel('Uszeregowane zadania wg algorytmu Jacksona.')
    ax[1].set_yticks([i*task_ysize for i in range(1,quantity)])
    ax[1].set_yticklabels(['Zadanie {}'.format(i) for i in range(1,quantity)])
    ax[1].set_ylim(0, quantity*task_ysize)
    ax[1].set_xlim(0, 1.01*max(c))
    major_ticks = np.arange(0, max(c)+1, 5)
    minor_ticks = np.arange(0, max(c)+1, 1)
    # ax[1].set_xticks(major_ticks)

  #  ax[1].set_xticks(minor_ticks, minor=True)
#    ax[1].grid(which='minor', alpha=0.3)
    ax[1].grid(which='major', alpha=0.8)
    ax[0].grid(which='major', alpha=0.8)
    fig.savefig("zobrazowanie_dzialania")

if __name__=='__main__':
    roz=[10,100,1000]
    for x in roz:
        testuj(x)

    #Pojedyncza wizualizacja
    roz=6
    r,p,ilosc=czytaj_dane(roz)
    C=jackson(r,p,ilosc)
    visualize(roz,r,p,C)



