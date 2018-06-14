# -*- coding: utf-8 -*-
import json
import threading
import heapq


class Lamport:
    def __init__(self):
        self.l = 0
        self.fila = []
        self.lock = threading.Lock()

    def TOM(self, event):
        t = 1
        try:
            event = event.split('\0')
            for j in event:
                if len(j) > 0:
                    i = json.loads(j)
                    id = int(i["id"])
                    lamp = int(i["lamp"])
                    msg = i["msg"]
                    n = str(lamp)+'.'+str(id)
                    heapq.heappush(self.fila, ((float(n), msg)))

        except ValueError as e:
            print 'lamport'
            print t
            print event
            print e
            pass

    def ordem(self):
        self.fila.sort(key=lambda x: x[0])
        return self.fila
