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
abspath = os.path.join(os.getcwd(), filename)
filesize = os.stat(abspath)

result = []
while block_size <= 100000: 
    #clearCache()
    start = time.perf_counter() 
    output = os.popen(f"./run {filename} -r {block_size} 10000000").read() #block count 10,000,000, size of file is 2.8 GB
    end = time.perf_counter()
    print("Program output:", output)
    result.append(output)
    dataRate = (filesize.st_size/1024.0/1024.0) / (end-start) 
    print("Python time: ", end - start, "Block size: ", block_size, "\n")
    block_size += 1000
    print("--------------------------------------")

actual_result = []
for i in result: 
    varb = i.split("\n")
    actual_result.append(varb[2].split(": ")[1].strip())

print(actual_result)




#parsed = [float(i) for i in output.split() if float(i) else ]
#print("Program output: \n", parsed)