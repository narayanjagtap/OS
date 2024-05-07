#!bin/bash
create()
{
	echo "Enter filename:"
	read filename
	
	if [ -f $filename ]
	then echo "!!!File already exists!!!"
	else touch $filename
		echo "*Address Book CREATED*"
	fi

	
}

insert()
{
	echo "Enter no. of records which want to insert"
	read n
	echo "Inserting Data"
	echo "RollNo.	Name	Mob	Email_id	City"
 	for((i=1;i<=n;i++))
	do
		read records
		echo $records >> $filename

		#n=` expr $n - 1`
	done
	echo "*RECORDS INSERTED*"
}

display()
{
	echo "*STUDENTS ADDRESS BOOK*"
	echo "RollNo.	Name	Mob	Email_id	City"
	cat $filename
}

search()
{
	echo "Enter the RollNo. to search:"
	read rollno
	
	
		if(grep -q "$rollno" $filename)
		then echo "RECORD FOUND"	
		echo "RollNo.	Name	Mob	Email_id	City"
		grep -i "$rollno" $filename 
		else echo "RECORD NOT EXISTS"
		fi
	
}

delete()
{
	echo "Enter the Roll No. to be deleted:"
	read rollno

	if(grep -q "$rollno" $filename)
	then grep -v "$rollno" $filename > filename1
		mv filename1 $filename
	     echo "**RECORD DELETED**"
	else echo "**RECORD NOT FOUND N WILL NOT BE DELETED**"
	fi
}

modify()
{
	echo "Enter the Roll No. which want to modify:"
	read rollno

	if(grep -q "$rollno" $filename)
	then echo "*Enter New Record*"
		echo "RollNo.	Name	Mob	Email_id	City"
		read newrecord
		sed -i "/$rollno /c $newrecord" $filename
	echo "**RECORD MODIFIED**"
	else echo "**RECORD NOT FOUND***"
	fi
}
	
		


#Switch Case:
until [ " $choice " = " 7 " ]
do echo "ADDRESS BOOK MENU:"
echo "1.CREATE Address Book"
echo "2.Insert"
echo "3.Display"
echo "4.Search"
echo "5.Delete"
echo "6.Modify"
echo "7.Quit"
echo "Enter ur choice:"
read choice

case $choice in
1)create;;
2)insert;;
3)display;;
4)search;;
5)delete;;
6)modify;;
esac

done





