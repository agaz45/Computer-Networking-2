import socket
import sys
import json
import random

def decrypt(encryptedMessage, key):
  random.seed(key)
  message = ''
  for i in encryptedMessage:
    rand = random.randint(0, 255)
    #get the ascii value of the char, convert a xor with the rand number, and then return the xorred ascii char
    message += chr(ord(i)^rand)
  return message

#initialize variables
g = 9
prime = 1001 
secret = 4
serverKey = (g ** secret) % prime

#setup a json for first delivery of variables (g, prime, and serverKey)
setupJson = "{"
setupJson += "\"g\": %s," %  str(g)
setupJson += "\"prime\": %s," % str(prime)
setupJson += "\"serverKey\": %s" % str(serverKey)
setupJson += "}"

# Create a TCP/IP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the port
server_address = ('localhost', 3001)
print('starting up on %s port %s' % server_address)
s.bind(server_address)

#Listen for incoming connections
s.listen(1)

connection, client_address = s.accept()
try:
  print('sending initial values and serverkey: %s' % serverKey)
  connection.send(setupJson.encode())

  #serverKey is not the actual key but the calculated portion with g and prime
  clientKey = connection.recv(1024)
  clientKey = int(clientKey.decode())
  sharedKey = (clientKey ** secret) % prime
  print("sharedKey: %s" % sharedKey)

  #receive message
  encryptedMessage = connection.recv(1024)
  receivedMessage = encryptedMessage.decode()
  message = decrypt(receivedMessage, sharedKey)
  print("Message: %s" % message)
finally:
  connection.close()
