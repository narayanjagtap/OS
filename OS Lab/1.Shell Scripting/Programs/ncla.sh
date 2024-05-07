n=$1
str=$2
i=1
while test $i -le $n
do
echo "$str"
i=`expr $i + 1`
done

