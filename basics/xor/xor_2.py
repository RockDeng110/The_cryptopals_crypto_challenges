#!/usr/bin/env python3

hex_str1 = "1c0111001f010100061a024b53535009181c"
hex_str2 = "686974207468652062756c6c277320657965"

# use methond of bytes.fromhex(a_str) trans a string representing with hexadecimal digits to bytes object.
bytes_1 = bytes.fromhex(hex_str1)
bytes_2 = bytes.fromhex(hex_str2)

print("bytes_1:{}".format(bytes_1))
print("bytes_2:{}".format(bytes_2))

bytes_3 = bytes([a ^ b for a, b in zip(bytes_1, bytes_2)])
print("bytes_3:{}".format(bytes_3))

# bytes.hex() method is the reverse of bytes.fromhex()
bytes_3_str = bytes_3.hex()
print("bytes_3_str:{}".format(bytes_3_str))
