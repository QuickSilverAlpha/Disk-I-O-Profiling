#!/usr/bin/env bash

gcc -O3 -fno-stack-protector -pthread helpers.c run.c -o run -lm
