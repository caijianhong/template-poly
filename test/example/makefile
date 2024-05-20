%: %.cpp ../../poly/*
	g++ $< -o $@ -O2 -g -DNF -DLOCAL -fsanitize=undefined,address -I../../poly -Wall -std=c++14
.PHONY: clean
clean:
	rm -f main $(patsubst %.cpp, %, $(wildcard *.cpp)) log
	find . -name '*~' | xargs rm -f

