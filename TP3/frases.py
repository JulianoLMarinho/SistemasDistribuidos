# -*- coding: utf-8 -*-

def getFrases():
    frases = []
    arquivo = open('quotes.txt', 'r')
    for linha in arquivo:
        frases += [linha]
    arquivo.close()
    return frases