n=$1
rev=0
while test $n -gt 0
do
rev=`expr $rev \* 10 + $n % 10`
n=`expr $n / 10`
done
echo The reverse is  $rev
