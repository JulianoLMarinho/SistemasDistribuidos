# -*- coding: utf-8 -*-
import errno
import os

class Arquivo:
    def __init__(self, id, n, k, lamb):
        self.n = n
        self.k = k
        self.lamb = lamb
        self.arquivo = open('log'+str(n)+'-'+str(k)+'-'+str(lamb)+'-'+str(id)+'.txt', 'w')


    def escreverLog(self, events):
        self.arquivo.write('id; lamport; mensagem\n')
        for i in events:
            a = str(i[0]).split('.')
            log = a[1]+";"+a[0]+";"+i[1]+"\n"
            self.arquivo.write(log)

    def closeFile(self):
        self.arquivo.close()


