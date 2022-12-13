# Disk-I-O-Profiling

2022-10-28 by Kamen

This is WIP draft of the final project. Please post comments!

This is the final project for [CS-GY 6233 2021 Fall](https://brightspace.nyu.edu/d2l/home/133560) ****and it is by its very nature quite open ended. Some of the ground rules that you are used to from homework do apply though:

- Work together at most with a single partner;
- Work should be your own / no cheating;

The environment for this project is real Linux (I recommend a recent Ubuntu, but really any recent distribution should work). You can use C or C++.

<aside>
💡 You can try to make it work on xv6 for extra credit... but you cannot exclusively use xv6. We have discussed in class that the biggest file xv6 can handle is 70KB. This will not be an interesting size to do all this assignment requires.

</aside>

The final project is 35% of your total grade. I will use discretion when grading it on what deserves [extra] credit. I will provide examples below. If you want to excel at this project you should consider some of the extra credits and possibly come up with more ideas of your own!

## Goal

The project is centered around performance.

We will try to get disk I/O as fast as possible and evaluate the effects of caches and the cost of system calls. In the end you should have a good understanding of what sits in the way between your process requesting data from disk and receiving it.

## Breakdown

### 1. Basics

- Write a program that can read and write a file from disk using the standard C/C++ library's `open`, `read`, `write`, and `close` functions.
    - Add parameter for the file name;
    - Add parameter for how big the file should be (for writing);
    - Add a parameter to specify how much to read with a single call (block size);

Way to execute: `./run <filename> [-r|-w] <block_size> <block_count>`

**Expected output**: For write (-w flag) a new file should be created with name as <filename>. The content written to the file can be any garbage value and the size of the file should be block_size * block_count bytes. Print the performance of write the file in MBs/sec or bytes/sec. 

For read (-r flag) your code should read file from the start and the number of bytes read should be equal to block_size * block_count. You will need to XOR the content read and print it to the terminal. Along with the XOR value print the performance in MiB/s or bytes/sec. 

### 2. Measurement

When measuring things it helps if they run for "reasonable" time. It is hard to measure things that run too fast as you need high-precision clocks and a lot of other things can affect the measurement. It is also annoying to wait for a long time for an experiment, especially if you have to do many experiments. For this reason you should make sure that your experiments take "reasonable" time. I recommend something between 5 and 15 seconds.

- Write a program to find a file size which can be read in "reasonable" time.
    - Input: block size
    - Output: file size

<aside>
💡 Hint: You can start with a small file size and use your program from (1) above to read it and measure the time it takes. You can keep doubling your file size until you get between 5 and 15 seconds.

</aside>

**How to run :** `./run2 <filename> <block_size>`  

**Expected Output:** Given the file and block_size output the block_count for which the time taken is between 5 and 15. The output for this case should be the XOR value, the file size for which the read time is between 5 and 15 sec, and the performance of reading the file in MiB/s or bytes/sec.

### 3. Raw Performance

Because you would be looking at different file sizes when using different block sizes, it makes sense to use units for performance that are independent of the size. Use MiB/s (this is megabytes per second).

- Make your program output the performance it achieved in MiB/s
- Make a graph that shows its performance as you change the block size.
    - block size on the x axis and performance on the y axis.

We will not mandate a way to run this... anything that works for you to produce the graphs.

**Expected Output:** In this case you will read the entire file by varying the block size. Plot a graph in your report with block size on the x axis and performance on the y axis.

### 4. Caching

Once you have a file of "reasonable" size created, reboot your machine.

Call your program to read the file and note the performance.

Call your program to read the file again (immediately after) and note the performance.

Ideally you should observe the second read be much faster, assuming the file can fit in your physical memory. This is the effect of caching.

<aside>
💡 NOTE: On Linux there is a way to clear the disk caches without rebooting your machine. E.g. `sudo sh -c "/usr/bin/echo 3 > /proc/sys/vm/drop_caches"`. 

**Extra credit:** Why "3"? Read up on it and explain.

</aside>

Experiment with clearing the caches and not.

- Make a graph that shows performance for cached and non-cached reads for various block sizes.

We will not mandate a way to run this... anything that works for you to produce the graphs.

**Expected Output:** Same as 3, just add the performance reading for cached file. The file blocks can be cached by reading the file multiple times. 

### 5. System Calls

If you have very, very small block size (e.g. 1 byte), most of the time would be spent trapping into the kernel. We talked in class how system calls are expensive. Let's quantify it!

- Measure performance MiB/s when using block size of 1 byte
- Measure performance in B/s. This is how many system calls you can do per second.
- Try with other system calls that arguably do even less real work (e.g. lseek)

We will not mandate a way to run this... anything that works for you to produce the graphs.

**Expected Output:** A graph comparing the read system call and other system call that does relatively less work like lseek. You need to plot a graph with number of system calls on the y-axis and time taken on x-axis.  

### 6. Raw Performance

Try to optimize your program as much as you can to run as fast as it could.

- Find a good enough block size?
- Use multiple threads?
- Report both cached and non-cached performance numbers.

### File required to submit

1. build - This should a binary file of build.c  or a .sh file which would compile all your files required for this project. 
2. run.c - This file should take 4 arguments (filename, either -w or -r, block_size, block_count)
3. run2.c - This file should take 2 arguments (filename, block_size)
4. fast.c - This file should take only one argument filename. The output should be the maximum performance you got and its corresponding block size.
5. Report - Include explanation and code screenshots for each section and graphs.

## Conclusion

This is a living document and will be updated as many of you have questions. Don't hesitate to put comments right on the document. Ideas for extensions are also welcome!

Enjoy, 

Kamen

# Appendix

Example code for xor:

```c
#include <stdio.h>

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

#define SIZE 100

int main()
{
    
    unsigned int buffer[SIZE] = {};
    
    // random initialization
    for (int i = 1; i < SIZE; i++) {
        buffer[i] = buffer[i - 1] * 31 + 17;
    }
    
    // compute xor one way...
    printf("%08x\n", xorb**uf(**buffer**,** SIZE));
    
    // compute xor another way... (as if 2 threads to half each)
    unsigned int xor1 = xorbuf(buffer, SIZE / 2);
    unsigned int xor2 = xorbuf(buffer + SIZE / 2, SIZE / 2);
    printf("%08x = %08x ^ %08x\n", xor1 ^ xor2, xor1, xor2);
    
    return 0;
}
```

# FAQ

## Is it necessary to use block count when in read mode?

Yes! 

`./run <filename> [-r|-w] <block_size> <block_count>`

Always use `block_size` and `block_count` as specified in the command line above.

File size is just `block_size * block_count`!

If you are reading, make sure you have a file big enough for that... it's size should be at least `block_size * block_count`! One way to do this is to create a large file first and then use it for all your reads.

Maybe add a check in the beginning of the program to see if the file has enough bytes and exit if the file is not big enough to accommodate reading that many blocks of the specified size!

If you did your analysis and produced numbers in a different way, as long as you used the right block size you should be fine for graphs and performance metrics. But make sure that you have a program that reads just the right amount for grading purposes so the TAs can check your XOR values.

## Can you provide a sample file and the correct XOR result so we can test our program with it?

Maybe many people can download a commonly available large file like this one [http://www.releases.ubuntu.com/21.04/ubuntu-21.04-desktop-amd64.iso](http://www.releases.ubuntu.com/21.04/ubuntu-21.04-desktop-amd64.iso) ... and compare their XOR values? If there is still concern, I will do the same 🙂

## Is the blockSize argument always a multiple of 4? Since an integer is 4 bytes?

We will always use multiples of 4, but you will have to run some experiments with `block_size` for one of the problems... just make sure your code does not crash on it. When we run for performance we will always use a multiple of 4.

## Does it matter what content we write to the files?

No. You can write whatever happens to be in memory inside your buffer — no need to put in anything special in there.

## Should we be measuring CPU time or wall time?

Wall time! CPU time is likely to be close to 0 since the problem is I/O Bound... unless you use a really small block size.

## If the inputs are then same, is it okay that xor is different?

No, XOR is a deterministic function and produces the same output for the same input.

## Does the file we read have to be in a specific format?

No special format required, but you should be reading the file as a binary... every 4 bytes being treated as an integer. Linux already does that with `open`, `read`, etc... Don't use `fopen`, `fread` and such — those are not system calls they are C library functions which internally call `open` and `read` but might be doing their own buffering and other trickery.

## 6. Raw Performance — how to?

Let's have everybody produce a program or a script called `fast` which accepts a single parameter — a file name. The program should read the file as fast as it can, compute the XOR for the whole file and print it out. The size of the file will be a multiple of 4.

`./fast <file_to_read>`

If the correct XOR number is printed we will compute the performance of the read as part of grading by dividing the size of the file to the time taken and will create a wall of fame for the whole class. We will publish the top 10 results.

## What do we have to submit in the final report?

- PDF of the report
- TAR.GZ of the code
- the regular "partner" stuff to make sure we know who worked with whom

## How to run?

- Q1: `./run <filename> [-r|-w] <block_size> <block_count>`
- Q2: `./run2 <filename> <block_size>`
- Q6: `./fast <file_to_read>`

How you run 2-5 is up to you as long as your graphs are clear.

Make sure that `./build` compiles everything we would need to run Q1, Q2,..., and Q6.
