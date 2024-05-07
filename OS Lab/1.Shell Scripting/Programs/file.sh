
#! Shell Script for File Handling Operation

clear
ch=1
while test ${ch} -ne 6 
do 
echo " Menu"
echo "1.create a file"
echo "2.add a new  record"
echo "3.display a record"
echo "4.modify a record"
echo "5.delete a record"
echo "6.exit"

echo "enter  your choice :"
read ch
case $ch in

1) echo " enter the file name to create "
   read filename
   touch $filename
   ;;
2) echo " enter the roll no of the student"
   read rollno 
   echo "enter the name "
   read name
   echo "$rollno | $name" >> $filename 
   ;;
3) echo "the records in the file are :"
   cat $filename
   ;;
4) echo  "enter the roll no to modify:"
   read rollno
   echo  " enter the new rollno:"
   read no
   echo  "enter the name "
   read name
   grep -v $rollno $filename > abc.dat
   echo " $no | $name " >> abc.dat
   rm $filename
   mv abc.dat $filename
   echo "file after modification "
   cat $filename 
   ;;
5) echo  " enter the roll no to be deleted "
   read no 
if (no -ne $rollno < $filename)
then
echo "Roll no does not exists "
else

   grep -v $no $filename > xyz.dat
   rm $filename
   mv xyz.dat $filename
   cat $filename 
fi
   ;;

6) break 
   ;;
esac 
done


