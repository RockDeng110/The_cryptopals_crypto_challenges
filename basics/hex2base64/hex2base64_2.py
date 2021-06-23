#!/usr/bin/env python3

import base64

hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
print("hex_str:{}".format(hex_str))
bytes_hex_str = bytes.fromhex(hex_str)
print("byres_hex_str:{}".format(bytes_hex_str))
base64_bytes = base64.b64encode(bytes_hex_str)
print("base64_bytes:{}".format(base64_bytes))
base64_str = base64_bytes.decode('ascii')
print("base64_str:{}".format(base64_str))

