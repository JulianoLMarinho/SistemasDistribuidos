# -*- coding: utf-8 -*-
from select import select
from socket import socket, AF_INET, SOCK_STREAM
import sys
import threading
import pickle

import Lamport


class Server():
    def __init__(self, host="localhost", port=9000):

        self.clients = []
        self.clientsSelect = []
        self.sock = socket(AF_INET, SOCK_STREAM)
        self.sock.bind((host, int(port)))
        self.sock.listen(5)
        self.sock.setblocking(False)
        self.lock = threading.Lock()

        # h = ''
        # if (h != ''):
        #     host = h

        accept = threading.Thread(target=self.acceptConnection)
        #process = threading.Thread(target=self.processConnection)

        accept.daemon = True
        accept.start()

        # process.daemon = True
        # process.start()

        # while True:
        #     msg = raw_input()
        #     if msg == 'exit()':
        #         self.sock.close()
        #
        #     else:
        #         pass

    def sendToAll(self, msg):
        for c in self.clients:
            try:
                # if c[0] != client[0]:
                c[0].send(msg+'\0')
            except ValueError as e:
                print msg
                print '1'
                print e
                #self.retry(c[0], msg)
                pass
                #self.clients.remove(c)
                #self.clientsSelect.remove(c[0])

    def acceptConnection(self):
        while True:
            r = [self.sock]
            ler, k, p = select(r, [], [])
            try:
                conn, addr = self.sock.accept()
                conn.setblocking(False)
                self.clients.append((conn, addr))
                self.clientsSelect.append(conn)
                # conn.send("Você entrou na conversa!")
                # print "Conectado com " + addr[0]
            except ValueError as e:
                print '2'
                print e
                pass

    # def processConnection(self):
    #     # print "Conectado..."
    #     while True:
    #         ler, k, p = select(self.clientsSelect, [], [], 1)
    #         if len(self.clients) > 0:
    #             for client in self.clients:
    #                 try:
    #                     msg = client[0].recv(1024)
    #                     if msg:
    #                         self.sendToAll(msg)
    #                 except ValueError as e:
    #                     print e
    #                     pass
