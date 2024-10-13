#!/bin/bash
make main ||exit 1
ulimit -s 1000000
for f in `find data -name '*.in'`; do
  \time ./main < $f | diff - ${f%.*}.out -sqBZ || exit 1
done

