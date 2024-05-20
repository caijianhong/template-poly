%: %.cpp ../../poly/*
	g++ $< -o $@ -O0 -g -DNF -DLOCAL -fsanitize=undefined,address -I../../poly -Wall -std=c++14
.PHONY: clean ALL
ALL: $(patsubst %.cpp, %, $(wildcard *.cpp))
clean:
	rm -f main $(patsubst %.cpp, %, $(wildcard *.cpp)) log
	find . -name '*~' | xargs rm -f

