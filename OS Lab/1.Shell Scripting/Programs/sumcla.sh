#Title:Program for sum of individual digit of four digit number using command line
#Roll no:20

echo "Progam Name:$0"
echo "No.of arguments :$#"
echo "Argument:$*"
a=$1
c=0
n=`echo $a | wc -c`
n=`expr $n - 1`
i=0
while test $i -lt $n
do
b=`expr $a % 10`
c=`expr $c + $b`
a=`expr $a / 10`
i=`expr $i + 1`
done
echo "Sum=$c"



