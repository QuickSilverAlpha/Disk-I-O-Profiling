import os
import copy

optimal_block_speed = 0
script_path = os.path.join(os.getcwd(), "calc_bc_modified.sh")
output = os.popen(f"{script_path}").read()

for perf_tuple in output.splitlines():
    blocksize = perf_tuple.split(":")[1].strip()

    rate_list = perf_tuple.split(":")[0].split(" ")

    if rate_list[1].strip() == "GB/s":
        tmp_block_speed = float(rate_list[0]) * 1024

    else:
        tmp_block_speed = float(rate_list[0])

    if tmp_block_speed > optimal_block_speed:
        optimal_block_speed = copy.deepcopy(tmp_block_speed)
        optimal_block_size = blocksize

print(int(optimal_block_size))
