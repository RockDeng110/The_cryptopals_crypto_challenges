#!/usr/bin/env python3

import codecs

hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"

print("type hex_str:{}".format(type(hex_str)))
hex = codecs.decode(hex_str, 'hex') # decode it from bytes to hex string 
print("type hex:{}".format(type(hex)))
print(hex)

b64 = codecs.encode(hex, 'base64').decode() # encode it from string to base64 bytes and then decode it to string

print(b64)
