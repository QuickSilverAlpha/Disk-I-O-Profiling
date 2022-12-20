import os

def clearCache():
    cmd = 'sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"'
    os.system(cmd)  

#Part 5
filename = "ubuntu-21.04-desktop-amd64.iso"
block_size = 1
block_count = 1000000
abspath = os.path.join(os.getcwd(), filename)
filesize = os.stat(abspath)

result = []
while block_count <= 100000000: 
    # clearCache()
    output = os.popen(f"./run5 {filename} {block_size} {block_count}").read()
    print("Program output:", output)
    result.append(output)
    block_count += 1000000
    print("--------------------------------------")

for i in result: 
    varb = i.split("\n")
    read_time = varb[4].split(": ")[1].strip()
    lseek_time = varb[7].split(": ")[1].strip()
    print(f"{block_count}:{read_time}:{lseek_time}")

