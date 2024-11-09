#!/bin/sh
hyperfine --warmup 100 --runs 10000 "$PWD/trolley < $PWD/trolley.txt" "$PWD/trolley_new < $PWD/trolley.txt"
