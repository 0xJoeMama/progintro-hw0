#!/bin/sh
hyperfine --warmup 10 --runs 1000 "$PWD/trolley < $PWD/trolley.txt"
