src = $(wildcard *.hpp)
tar = $(patsubst %.hpp, %.gch, $(src))
%.gch: %.hpp $(src)
	g++ -c $< -o $@ -Wall -std=c++14 -g -O2
.PHONY: clean ALL
ALL: $(tar)
clean:
	clang-format -i $(src)
	find . -name '*~' | xargs rm -f
	rm -f $(tar) .depend
