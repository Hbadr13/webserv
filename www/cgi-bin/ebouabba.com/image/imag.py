#!/usr/bin/env python3

import sys
import os

src =  "file.png"
length = os.stat(src).st_size

sys.stdout.write("Content-Type: image/png\n")
sys.stdout.write("Content-Length: " + str(length) + "\n")
sys.stdout.write("\n")
sys.stdout.flush()
sys.stdout.buffer.write(open(src, "rb").read())