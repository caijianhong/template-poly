#!/usr/bin/python3
import os, sys
module = input("module name: ").strip()
with open(f"./test/main.cpp", "w") as file:
    file.write(open(f"./poly.cpp", "r").read() + open(f"./test/{module}.cpp").read())
if os.system(f"g++ ./test/main.cpp -o main -O2 -fsanitize=undefined,address -Wall -std=c++14"):
    input("CE...")
    sys.exit(0)
if os.system(f"./main < ./test/{module}_1.in > ./test/{module}_1.out"):
    input("RE...")
    sys.exit(0)
if os.system(f"diff ./test/{module}_1.out ./test/{module}_1.ans -bB"):
    input("WA...")
    sys.exit(0)
print("passed samples test")
