#!/usr/bin/env bash

gcc -O3 -Wall helpers.c run.c -o run -lm

gcc -O3 -Wall helpers.c run2.c -o run2 -lm
