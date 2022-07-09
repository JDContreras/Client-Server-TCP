#! /usr/bin/python3
import typer  #it could be used any other cli library, but i love typer since i use fastapi
import socket
import sys

class echoClient():
    def __init__(self, _ip, _port):
        self._ip = _ip
        self._port = _port
        try: 
            self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except socket.error as e: 
            print ("Error creating socket: %s" % e) 
            sys.exit(1) #get out 

    def connect(self):
        try:
            self.client.connect((self._ip ,self._port))
        except socket.gaierror as e: 
            print ("error connecting to server: %s" % e) 
            print ("check endpoint and try again") 
            sys.exit(1) 
        except socket.error as e: 
            print ("Connection error: %s" % e) 
            sys.exit(1)
        
    def send(self, message):
        self.connect() #make sure it is connected, so connect is no required to be used before
        try:
            encode_message = message.encode('utf-8')+ b"\n"
            #print(encode_message)
            self.client.sendall(encode_message) #from typer i ensure that message is string
        except socket.error as e: 
            print ("Error sending data to server: %s" % e) 
            sys.exit(1)
    
    def waitForEcho(self):
        try:
            echo = self.client.makefile("rb")
            for f in echo.readlines():
                if f != b'\n':
                    clean_data = f.decode("utf-8").strip()  #conver byte to string and clean '\n'
            
            return clean_data
        except socket.error as e: 
            print ("Error receiving data from server: %s" % e) 
            sys.exit(1)

    


def main(
    reverse: str = typer.Option(..., help = "text to reverse in server"), 
    endpoint: str = typer.Option("0.0.0.0:8080", help ="endpoint of the listening server in the format HOST:PORT"),
    ):
    ep = str(endpoint).split(":")
    IP = ep[0]
    PORT = int(ep[1]) #todo: validate that port is int
    c = echoClient(IP, PORT)
    c.send(reverse)
    typer.echo(typer.style(c.waitForEcho(), fg=typer.colors.GREEN, bold=True))


if __name__ == "__main__":
    typer.run(main)
