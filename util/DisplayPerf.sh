#!/bin/sh

a=`ls -t -r *.perf`
for b in $a
do
	less $b
done;
