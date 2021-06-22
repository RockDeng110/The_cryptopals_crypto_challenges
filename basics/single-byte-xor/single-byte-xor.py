#!/usr/bin/env python3

import codecs

encoded_hex_str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

decoded_hex = []


encoded_hex = codecs.decode(encoded_hex_str, 'hex')
print("encoded_hex:{}".format(encoded_hex))

#keys = range(0,255)
#print("keys:{}".format(keys))

for x in range(256):
<<<<<<< HEAD
    decoded_hex = bytes([a ^ x for a in encoded_hex]) 
    decoded_str = codecs.decode(decoded_hex, 'ascii')
    print("key={}".format(x))
    print(decoded_str)
=======
   decoded_hex = bytes([a ^ x for a in encoded_hex]) 
   decoded_str = codecs.encode(decoded_hex, 'hex')
   print("key={}".format(x))
   print(decoded_str)
>>>>>>> 1ad318e4bfb5d2c0c648bfe27381ca3ba2a6c7c2
