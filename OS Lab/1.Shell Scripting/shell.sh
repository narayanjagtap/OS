# Assignment No. 1: Shell programming
# Write a program to implement an address book with options given below:
# a) Create address book. b) View address book. c) Insert a record. d) Delete a record.
# e) Modify a record. f) Exit.

#!/bin/bash



clear
i="y"
echo "enter the name of your database .."
read db
while [ $i = "y" ]
clear
do
echo "1.view db"
echo "2.insert record"
echo "3.delete record"
echo "4.modify record"
echo "5.exit"
echo "enter your choice .."
read ch
case $ch in
1) cat $db;;

2) echo "lets insert a new record ..."
   echo "enter roll "
   read sroll
   echo "enter name "
   read sname
   echo "enter clg name "
   read sclg
   echo "$sroll $sname $sclg">>$db
   echo "record inserted successfully ...";;

3) echo "lets delete a new record ..."
   echo "enter roll to be deleted"
   read srollroll
   grep -v "$srollroll" $db>>db1 // -v, --invert-match Invert the sense of matching, to select non-matching lines.

   mv db1 $db
   echo "record deleted successfully ...";;

4) echo "enter roll to be modified"
   read ssroll
   grep -v "$ssroll" $db>>db1
   mv db1 $db

   echo "enter roll "
   read sroll
   echo "enter name "
   read sname
   echo "enter clg name "
   read sclg
   echo "$sroll $sname $sclg">>$db
   echo "record modified successfully ...";;

5) exit;;

*) echo "invalid choice ...." ;;
esac
echo "do u want to continue ???"
read i
if [ $i != "y" ]
then 
exit
fi
done


