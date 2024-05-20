%: %.cpp ../../poly/*
	g++ $< -o $@ -O0 -g -DNF -DLOCAL -fsanitize=undefined,address
.PHONY: clean
clean:
	rm -f main $(patsubst %.cpp, %, $(wildcard *.cpp))
	find . -name '*~' | xargs rm -f

