#!/usr/bin/env python3

#encoded_hex_str = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
#
#bytes_1 = bytes.fromhex(encoded_hex_str)
#print("bytes_1:{}".format(bytes_1))

bytes_s1 = b'this is a test'
bytes_s2 = b'wokka wokka!!!'
bytes_s3 = bytes([a ^ b for a, b in zip(bytes_s1, bytes_s2)])
print(bytes_s3)

bin_str = str(bin(int(bytes_s3.hex(), base=16)))

count = 0
for c in bin_str:
    if c == '1':
        count = count +1


print("count:{}".format(count))
 
#for x in range(256):
#    bytes_xored = bytes([a ^ x for a in bytes_1]) 
#    bytes_xored_str = bytes_xored.hex()
#    print("key={}".format(x))
#    print("bytes_xored_str:{}".format(bytes_xored_str))
