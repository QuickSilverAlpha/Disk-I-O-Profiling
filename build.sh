#!/usr/bin/env bash

gcc -Wall helpers.c run.c -o run -lm
gcc -Wall helpers.c run2.c -o run2 -lm
gcc -O3 -Wall helpers.c run5.c -o run5 -lm
gcc -O3 -Wall helpers.c fast.c -o fast -lm
