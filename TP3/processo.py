# -*- coding: utf-8 -*-
import Lamport
from config import getConf
from frases import getFrases
from log import Arquivo
import time
from Cliente import Cliente
from Servidor import Server
import sys
import random
import portas

id = int(sys.argv[1])             #id do processo
n = int(sys.argv[2])         #número de processos
lamb = int(sys.argv[3])  #taxa de frases por segundo
k = int(sys.argv[4])        #frases geradas
frases = getFrases()
c = []
confs = getConf()
iconf = []
for i in confs:
    if i[0] == id:
        iconf = i

portasR = portas.portas[str(n)][str(k)][str(lamb)]
s = Server(iconf[1], portasR[str(id)])

lamp = Lamport.Lamport()
arquivo = Arquivo(int(id), n, k, lamb)



def iniciaCliente(s):
    for i in range(0, n):
        if i+1 != id:
            c.append(Cliente(confs[i][1], portasR[str(i+1)], str(id), s , lamp))

time.sleep(5)

iniciaCliente(s)
t = True

time.sleep(5)

print('server e client iniciados')

tam = len(frases)
cont = 0

while t:
    time.sleep(1.0/lamb)
    h = frases[random.randint(0, tam-1)][:-2]
    # h = raw_input()
    if cont >= k:
        print "processo "+str(id)+" terminou. Aguardando 10s"
        time.sleep(10)
        s.sock.close()
        t = False
        arquivo.escreverLog(lamp.ordem())
        arquivo.closeFile()
    else:
        lamp.l += 1
        jsonObj = '{"id":"' + str(id) + '", "lamp":"' + str(lamp.l) + '", "msg":"' + h + '", "type":"primary"}\0'
        lamp.TOM(jsonObj)
        s.sendToAll(jsonObj)
        cont += 1