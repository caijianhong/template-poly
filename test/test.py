#!/usr/bin/python3
import os
module = input().strip()
with open(f"main.cpp", "w") as file:
    file.write(open(f"../poly.cpp", "r").read() + open(f"{module}.cpp").read())
os.system(f"g++ main.cpp -o main -O2 -fsanitize=undefined,address -Wall -std=c++14")
os.system(f"./main < {module}_1.in > {module}_1.out")
if os.system(f"diff {module}_1.out {module}_1.ans -bB"):
    input("error...")
