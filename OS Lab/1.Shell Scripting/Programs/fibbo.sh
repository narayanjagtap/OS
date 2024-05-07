#! Shell Script for printing Fibonacci Series
#!bin/bash

echo "fibbo series"
read limit 
a=0
b=1
d=1
echo "----------------"
echo -n $a
echo -n " "
while test $d -le $limit
do
c=`expr ${a} + ${b}`
echo -n $c
echo -n " "
b=$a
a=$c
d=`expr $d + 1`
done




