#!/usr/bin/env python3

import codecs

hex_str1 = "1c0111001f010100061a024b53535009181c"
hex_str2 = "686974207468652062756c6c277320657965"


hex1 = codecs.decode(hex_str1, 'hex')
hex2 = codecs.decode(hex_str2, 'hex')

print(type(hex1))
print(hex1)
print(hex2)

hex3 = bytes([a ^ b for a, b in zip(hex1, hex2)])
hex3_str = codecs.encode(hex3, 'hex')
print(hex3_str)
