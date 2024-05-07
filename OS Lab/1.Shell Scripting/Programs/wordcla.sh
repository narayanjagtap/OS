word=$1
n=$2
while test $n -gt 0
do
echo " $word "
n=`expr $n - 1`
done
