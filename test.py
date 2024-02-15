#!/usr/bin/python3
import os, sys
module = input().strip()
with open(f"./test/main.cpp", "w") as file:
    file.write(open(f"./poly.cpp", "r").read() + open(f"./test/{module}.cpp").read())
os.system(f"g++ ./test/main.cpp -o main -O2 -fsanitize=undefined,address -Wall -std=c++14")
os.system(f"./main < ./test/{module}_1.in > ./test/{module}_1.out")
if os.system(f"diff ./test/{module}_1.out ./test/{module}_1.ans -bB"):
    input("error...")
