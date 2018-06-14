# -*- coding: utf-8 -*-
from select import select
from socket import socket, AF_INET, SOCK_STREAM
from Tkinter import *
import threading
import sys
import pickle
import json
import Lamport

from Servidor import Server


class Cliente():
    def __init__(self, host="localhost", port=9999, name="usuário", s= Server, lamp = Lamport.Lamport):

        self.lamp = lamp
        self.name = name
        self.sock = socket(AF_INET, SOCK_STREAM)

        self.sock.connect((host, port))
        self.sock.setblocking(True)
        self.server = s
        msgFromServer = threading.Thread(target=self.msgFromServer)

        msgFromServer.daemon = True
        msgFromServer.start()

    def msgFromServer(self):
        while True:
            ler, r, w = select([self.sock], [], [])
            try:
                msg = self.sock.recv(1024)
                if msg:
                    msgTemp = msg.split('\0')
                    for i in msgTemp:
                        if len(i)>0:
                            data = json.loads(i)
                            l = max(int(data["lamp"]), self.lamp.l) + 1
                            self.lamp.l = l
                            if(data["type"] == "primary"):
                                jsonObj = '{"id":"' + str(data["id"]) + '", "lamp":"' + data["lamp"] + '", "msg":"' + data["msg"] + '", "type":"confirmation"}\0'
                                self.server.sendToAll(jsonObj)
                                self.lamp.TOM(i)
                            else:
                                """
                                """
                                # self.lamp.TOM(msg)
            except ValueError as e:
                print msg
                print '3'
                print e
                pass

    # def sendMessage(self, msg, lamp, type):
    #     jsonObj = '{"id":"' + self.name + '", "lamp":"'+lamp+'", "msg":"' + msg + '", "type":"'+type+'"}'
    #     self.server.sendToAll(jsonObj)
