#!/usr/local/bin/bash

num=200
average=0

for run in {1..200}
do
  timeSpent=$( TIMEFORMAT="%R"; { time ../cmake-build-release/all-pairs-shortest-path < ../tests/test_1.in > ../tests/test_1_actual.out 2> /dev/null; } 2>&1 )
  average=$(perl -e "print ${average} + ${timeSpent}")
  diff -u ../tests/test_1_expected.out ../tests/test_1_actual.out
done

echo $(perl -e "print ${average} / ${num}")
