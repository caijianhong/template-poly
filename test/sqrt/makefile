LIB = ../../src/
%: %.cpp $(LIB)
	g++ $< -o $@ -std=c++14 -O2 -g -DNF -Wconversion -Wall -Wextra -Wshadow -I$(LIB) -pthread -lbenchmark
%-O0: %.cpp $(LIB)
	g++ $< -o $@ -std=c++14 -O0 -g -DNF -Wconversion -Wall -Wextra -Wshadow -I$(LIB) -pthread -lbenchmark
%-combined.cpp: %.cpp
	../../expander.py -o $@ --lib $(LIB) $<
all: main
