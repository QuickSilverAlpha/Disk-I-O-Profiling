import os
import time
import sys

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
    output = os.popen(f"./fast {filename}").read() #block count 10,000,000, size of file is 2.8 GB
    end = time.perf_counter()
    print("Program output:", output)
    result.append(output)
    dataRate = (filesize.st_size/1024.0/1024.0) / (end-start) 
    print("Python time: ", end - start, "\n")
    print("Python time: ", end - start,"\n")
    block_size += 1000
    print("--------------------------------------")


actual_result = []
for i in result: 
    varb = i.split("\n")
    actual_result.append(varb[5].split(": ")[1].strip())

print(actual_result)
