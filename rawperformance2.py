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
    # clearCache()
    start = time.perf_counter() 
    output = os.popen(f"./fast {filename}").read() #block count 10,000,000, size of file is 2.8 GB
    end = time.perf_counter()
    print("Program output:", output)
    result.append(output)
    dataRate = (filesize.st_size/1024.0/1024.0) / (end-start) 
    print("Python time: ", end - start,"\n")
    block_size += 1000
    print("--------------------------------------")




#parsed = [float(i) for i in output.split() if float(i) else ]
#print("Program output: \n", parsed)