#!/bin/sh

a=`ls -t -r massif*`
for b in $a
do
	ms_print $b | less
done;
