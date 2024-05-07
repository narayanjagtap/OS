#!/bin/bash

createaddressBook()
{
echo
if [ -e addressbook.txt ]
then
echo "Address Book already created"
else
touch address book.txt
echo "adressbook created"
fi
}

insertARecord()
{
echo
while true
do
echo "To add a record to address book,please enter the information in this"
echo "format: \"Last name,first name,email,phone number \"."
echo "Example: verma,Rajat,rajatverma@gmail.com,1234567890"
echo "to quit press 'q'."
read aInput
if [ "$aInput" == 'q' ]
then 
break
fi
echo
echo $aInput>>addressbook.txt
echo "The record inserted in address book."
echo
done
}

viewRecord()
{
echo
while true
do
echo "To display a record,enter the last name of the person."
echo "to quit,press 'q'."
read dInput
if [ "$dInput" == 'q' ]
then 
break
fi
echo
echo "Display records for \"$dInput\":"
grep ^"$dInput" addressbook.txt
RETURNSTATES='echo $?'
if [$RETURNSTATUS -eq 1 ]
then 
echo "No records found with last name of \"$dInput\"."
fi
echo
done
}

modifyRecord()
{
echo
while true
do
echo "to modify a record,enter any search string ,e.g.last name or email address(case sensitive)."
echo "When finished editing address book ,enter 'q' to quit."
read eInput
if [ "$eInput" == 'q']
then
break
fi
echo
echo "Listing records for \"$eInput\":"
grep -n "$eInput" addressbook.txt
RETURNSTATUS='echo $?'
if [ $RETURNSTATUS -eq 1 ]
then 
echo "No records found for \"$eInput\""
else
echo
echo "Enter the line number that you'd like to edit."
read lineNumber
echo
for line in 'grep -n "$eInput" addressbook.txt'
do
number='echo "$line" | cut -c1'
if [ $number -eq $ lineNumber ]
then
echo "What would you like to change it to? Use the format:"
echo "\"Last name, first name, email url,phone number
read edit
lineChange="${lineNumber}s"
sed -i -e "lineChange/.*/$edit/"addressbook.txt
echo
echo "address book updated"
fi
done
fi
echo
done
}

deleteRecord()
{
echo
while true
do
echo "To remove a record,enter any search string,e.g.last name or email address"
echo "If finished,enter 'q' to quit."
read rInput
if [ "$rInput"=='q' ]
then
break
fi
echo
echo "Listing records for \"$rInput\":"
grep -n "$rInput" addressbook.txt
RETURNSTATUS='echo $?'
if [ $RETURNSTATUS -eq 1 ]
then 
echo "No records found for \"$rInput\""
else
echo
echo "Enter the line number of the record you want to remoe."
read lineNumber
for line in 'grep -n "$rInput" addressbook.txt'
do
number='echo "$line" | cut -c1'
if [ $number -eq $lineNumber ]
then
line remove="${lineNumber}d"
sed -i -e "$lineRemove" addressbook.txt
echo "The record was removed from the address book."
fi
done
fi
echo
done
}

searchRecord()
{
echo
while true
do
echo "To search for a record,enter any search string,e.g.last name or email address."
echo "The format of a record is \"Last name,firstname,email address,phone number\""
echo "Example:pratiksha,deshmukh,pratikshadeshmukh11@gmail.com,123456789"
echo "For exit,enter 'q'."
read sInput
if [ "$sInput" =='q' ]
then
break
fi
echo
echo "Listing records for \"$sInput\":"
grep "$sInput" addressbook.txt
RETURNSTATUS='echo $?'
if [ $RETURNSTSTUS -eq 1 ]
then
echo "No records found for \"$sInput\"."
fi
echo
done
}

echo
lastCharOfFile='tail -c 1 addressbook.txt' 
if [ -n "$lastCharOfFile" ]
then
echo >>addressbook.txt
fi
echo "address book?"
echo "Enter your choice"
echo "1-->>create address book"
echo "2-->>insert a record"
echo "3-->>view 1 or more records"
echo "4-->>modify a record"
echo "5-->>delete a single record"
echo "6-->>search for records"
echo "7-->>Exit"
echo
read input 
case $input in
     1) createAddressBook;;
     2) insertARecord;;
     3) viewRecord;;
     4) modifyRecord;;
     5) deleteRecord;;
     6) searchRecord;;
     7) EXIT;;
esac


