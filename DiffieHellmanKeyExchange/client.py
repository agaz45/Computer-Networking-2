import socket
import sys
import json
import random
import time

def encrypt(message, key):
  random.seed(key)
  encryptedMessage = ''
  for i in message:
    rand = random.randint(0, 255)
    #get the ascii value of the char, convert a xor with the rand number, and then return the xorred ascii char
    encryptedMessage += chr(ord(i)^rand)
  return encryptedMessage

#secret key for the cleint
secret = 7

# Create a TCP/IP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect the socket to the port where server is listening
server_address = ('localhost', 3001)
s.connect(server_address)

try:
  setupJson = s.recv(1024)
  jsonData = json.loads(setupJson.decode())

  # get all values of (g, prime and the serverKey
  #serverKey is not the actual key but the calculated portion with g and prime
  g = int(jsonData["g"])
  prime = int(jsonData["prime"])
  serverKey = int(jsonData["serverKey"])
  clientKey = (g ** secret) % prime
  print("clientKey: %s" % str(clientKey))

  #send the clientKey to the server
  s.send(str(clientKey).encode())
  sharedKey = (serverKey ** secret) % prime
  print("sharedKey: %s" % sharedKey)
  
  #this sleep needs to be present, otherwise it combines both sends in one.
  time.sleep(1)
  message = "This is a very important message that needs to be encrypted before it is sent. Please encrypt this!"
  encryptedMessage = encrypt(message, sharedKey)
  print("Sending Message: %s" % encryptedMessage)
  s.send(encryptedMessage.encode())
finally:
  s.close()
