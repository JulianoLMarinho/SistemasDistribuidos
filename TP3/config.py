# -*- coding: utf-8 -*-

def getConf():
    config = open('config.txt', 'r')
    conf = []
    for linha in config:
        temp = linha.split(',')
        conf.append([int(temp[0]), str(temp[1]), int(temp[2])])
    return conf