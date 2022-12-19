import os
import time
import sys
import matplotlib.pyplot as plt

def clearCache():
    cmd = 'sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"'
    os.system(cmd)  

#Part 2
filename = "ubuntu-21.04-desktop-amd64.iso"
block_size = 1000

while block_size <= 100000: 
    start = time.perf_counter() 
    output = os.popen(f"./run {filename} -r {block_size} 1000000").read() #block count 1,000,000, size of file is 2.8 GB
    stop = time.perf_counter()
    print("First test")
    print("Program output: \n", output)
    print("Python time: ", stop - start, "Block size: ", block_size)
    block_size += 1000

#parsed = [float(i) for i in output.split() if float(i) else ]
print("Program output: \n", output)

#print("Program output: \n", parsed)