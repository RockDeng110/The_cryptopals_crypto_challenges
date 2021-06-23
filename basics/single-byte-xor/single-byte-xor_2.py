#!/usr/bin/env python3

encoded_hex_str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

bytes_1 = bytes.fromhex(encoded_hex_str)
print("bytes_1:{}".format(bytes_1))


for x in range(256):
    bytes_xored = bytes([a ^ x for a in bytes_1]) 
    bytes_xored_str = bytes_xored.hex()
    print("key={}".format(x))
    print("bytes_xored_str:{}".format(bytes_xored_str))
