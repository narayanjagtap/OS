#! Menu Driven Shell Script for Palindrome,Factorial,Prime No,Greatest of 3 No

ch=1
while test $ch -ne 5
do 
echo  "\t***********Menu**********

1)palindrome of string or number
2)factorial
3)prime number
4)greatest of three number
5)EXit
Enter your choice : \c"
read ch
case "$ch" in

1)echo "enter a string to be entered:"
  read str
  echo
len=`echo $str | wc -c`
len=`expr $len - 1`
i=1
j=`expr $len / 2`
while test $i -le $j
do
k=`echo $str | cut -c $i`
l=`echo $str | cut -c $len`
if test $k != $l
then
echo "string is not palindrome"
exit;
fi
i=`expr $i + 1`
len=`expr $len - 1`     
done
echo "string is palindrome"
;;

2)echo "Enter a number:"
read n
fact=1
i=1
while test $i -le $n
do
fact=`expr $fact \* $i`
i=`expr $i + 1`
done
echo "Factorial of $n is $fact"
;;

3)echo " enter no : "
read n
i=2
tem=0
while [ $n -gt $i ]
do
k=`expr $n % $i`
if [ $k -eq 0 ]
then tem=1
fi
i=`expr $i + 1`
done
if [ $tem -eq 1 ]
then echo " no is not prime"
else
echo "no is prime"
fi
;;

4)echo "Enter 1st number :"
  read n1
  echo "Enter 2nd no:"
  read n2
  echo "Enter 3rd no:"
  read n3
if   [ $n1 -gt $n2 ] && [ $n1 -gt $n3 ] 
then    echo "$n1 or 1st no is greater"
elif [ $n2 -gt $n1 ] && [ $n2 -gt $n3 ] 
then    echo "$n2 or 2nd no is greater"
elif [ $n3 -gt $n1 ] && [ $n3 -gt $n2 ]
 then   echo "$n3 or 3rd no is greater"
elif [ $n1 -eq $n2 ] && [ $n2 -eq $n3 ] 
then    echo "all numbers are equal"
fi
;;
5)exit
;;
esac
done
