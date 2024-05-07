#!/bin/bash
echo
while true
do
PS3="Enter the Number : "
echo "What you want to do :"
select choice in "edit" "create" "delete" "enquire" "quit"
done
 if [ $choice = edit ] 2> error
 then
  while true
  do
   echo
   echo "Name of the friend"
   echo
   touch book
   cat -n book
   wc -l book > n1
   cut -d" " -f1 n1 > n2
   { read n1 ; } < n2
   echo
   if [ $n1 -eq 0 ]
   then
    echo "No record"
    echo
    break
   fi
   read -p "enter the number : " n 
   if [ $n1 -ge $n ] 2> error
   then   
    echo
    sed -n "$n"p book > n3
    { read n3 ; } < n3
    echo
    echo "your previous record is :"
    echo
    echo $n3
    echo  
   else
    echo
    echo "Invalid Input..."
    continue
   fi
   while true
   do
    read -p "do you want to edit it?(y/n) " -n1 w1
    echo
    if [ $w1 = y ]
    then
     while true
     do
      echo
      read -p "Enter the Friend name : " frnd

      cut -d: -f1 book > book1
      grep -w $frnd book1 > book2
      if [ $? = 0 ]
      then 
       echo
       echo "Name Already Exist"
       echo
       continue
      else
       break
      fi
     done
     echo
     while true
     do
      echo
      read -p "Enter the Email-id : " email

      cut -d: -f2 book > book1
      grep -w $email book1 > book2
      if [ $? = 0 ]
      then 
       echo
       echo "Email-id Already Exist"
       echo
       continue
      else
       break
      fi
     done
     echo
     read -p "Enter the Address : " address
     echo
     while true
     do
      echo
      read -p "Enter the Contact Number : " contact
  
      cut -d: -f4 book > book1
      grep -w $contact book1 > book2
      if [ $? = 0 ]
      then 
       echo
       echo "Contact Number Already Exist"
       echo
       continue
      else
       break
      fi
     done
     echo
     echo "$frnd:$email:$address:$contact" >> book
     while true
     do
      read -p "Are You Sure You Want To overwrite it ?(y/n)" -n1 w2
      echo
      if [ $w2 = y ]
      then
       cut -d: -f1 n3 > n4
       { read n ; } < n4
       grep -v $n book > .book1
       cat .book1 > book
       echo "Editing Succesful.."
       break
      elif [ $w2 = n ]
      then
       break
      else
       echo
       echo "incorrect input"
       echo
       continue
      fi
     done
     break
   elif [ $w1 = n ]
   then
    break
   else
    echo
    echo "incorrect input"
    echo 
    continue
   fi
   done
   echo
   while true
   do
    read -p "do you want to continue for edit (y/n) :" -n1 w3
    echo
    if [ $w3 = n ]
    then
     echo
     break
    elif [ $w3 = y ]
    then 
     echo
     break
    else
     echo
     echo "Invalid Input...."
     echo
     continue
    fi
   done
   if [ $w3 = n ]
   then
    break
   else
    continue
   fi
  done
 elif [ $choice = create ] 2> error
 then
  while true
  do
   echo
   while true
   do
    echo
    read -p "Enter the Friend name : " frnd
    touch book
    cut -d: -f1 book > book1
    grep $frnd book1 > book2
    if [ $? = 0 ]
    then 
     echo
     echo "Name Already Exist"
     echo
     continue
    else
     break
    fi
   done
   echo
   while true
   do
    echo
    read -p "Enter the Email-id : " email

    cut -d: -f2 book > book1
    grep $email book1 > book2
    if [ $? = 0 ]
    then 
     echo
     echo "Email-id Already Exist"
     echo
     continue
    else
     break
    fi
   done
   echo
   echo "Enter the Birth Date"
   while true
   do
    read -p " Enter the date : " date
    if [ $date -le 31 -a $date -ge 1 ] 2> error
    then
     break
    fi
   done
   while true
   do
    read -p " Enter the month : " month
    if [ $month -le 12 -a $month -ge 1 ] 2> error
    then
     break
    fi
   done 
   while true
   do
    read -p " Enter the Year : " year
    echo $year > year1
    wc -c year1 > year2
    cut -d" " -f1 year2 > year1
    { read year2 ; } < year1
    expr $year2 - 1 > year1
    { read year2 ; } < year1
   # if [ $year -ge 2012 ] 2> error
   # then
   #  echo $year > year3
   #  cut -c3,4 year3 > year4
  #   { read year3 ; } < year4 
     if [ $year2 -eq 4 ] 2> error
     then
      break
     fi
   # fi
   done
   read -p "Enter the Address : " address
   echo
   while true
   do
    echo
    read -p "Enter the Contact Number : " contact
  
    cut -d: -f4 book > book1
    grep $contact book1 > book2
    if [ $? = 0 ]
    then 
     echo
     echo "Contact Number Already Exist"
     echo
     continue
    else
     break
    fi
   done
   echo
   echo "$frnd:$email:$date/$month/$year3:$address:$contact" >> book
   echo
   echo "Created..."
   echo
   while true
   do
    read -p "do you want to continue to add (y/n) :" -n1 w4
    echo
    if [ $w4 = n ]
                  then
                          echo
                          break
                  elif [ $w4 = y ]
                   then
                   echo
                           break
                  else
                          echo
                          echo "Invalid Input...."
                          echo
                          continue
                  fi
   done
   if [ $w4 = n ]
   then
   break
   else
    continue
   fi
                done
 elif [ $choice = delete ] 2> error
 then
  while true
  do
   echo
   echo "Select the friend name : "
   echo  
   touch book  
   cat -n book
   wc -l book > n
   cut -d" " -f1 n > n1
   { read n ; } < n1
   echo
   if [ $n -eq 0 ]
   then
    echo "No record to delete"
    echo
    break
   fi
   read -p "enter the number : " del 
   echo
   if [ $del -le $n ] 2> error
   then
    while true
    do
     read -p "are you sure to delete? (y/n) :" -n1 w5
     if [ $w5 = y ]
     then
      sed -i "$del"d book
      echo
      echo "Deleted..."
      break
      echo
     elif [ $w5 = n ]
     then
      echo
      break
      echo
     else
      echo
      echo "Incorrect Input....."
      echo
      continue
     fi
    done
   else
    echo
    echo "Incorrect Input....."   
    echo
    continue
   fi
   echo
   while true
   do
    read -p "do you want to continue (y/n) :" -n1 w6
    echo
    if [ $w6 = n ]
    then
     echo
     break
    elif [ $w6 = y ]
    then
     echo
     break
    else
     echo
     echo "incorrect Input...."
     echo
     continue
    fi
   done
   if [ $w6 = n ]
   then
    break
   else
    continue
   fi
  done 
 elif [ $choice = enquire ] 2> error
 then
  while true
  do
   echo
   touch book
   cut -d: -f1 book > book1
   sed = book1 | sed 'N;s/\n/ /'> book2
   wc -l book2 > book3
   cut -d" " -f1 book3 > book4
   { read check1 ; } < book4
   echo
   if [ $check1 -eq 0 ]
   then
    echo "No record to enquiry"
    echo
    break
   fi
   while true
   do
    cat -n book1
    echo
    read -p "Select the Number : " check
    echo
    if [ $check1 -ge $check ]
    then
     echo
     sed -n "$check"p book2 > book1
     cut -d" " -f2 book1 > book2
     { read check2 ; } < book2
     grep -w $check2 book
     echo
     break
    else
     echo 
     echo "Incorrect Input"
     echo
     continue
    fi
   done
   while true
   do
    read -p "do you want to continue (y/n) :" -n1 w7
    echo
    if [ $w7 = n ]
    then
     echo
     break
    elif [ $w7 = y ]
    then
     echo
     break
    else
     echo
     echo "Invalid Input..."
     echo
     continue
    fi 
   done
   if [ $w7 = n ]
   then
    break
   else
    continue
   fi
  done
 else
  break
 fi
 break
done
 if [ $choice = quit ] 2> error
 then
  echo
  break
  echo
 elif [ $choice != quit ] 2> error
 then
  echo
  continue
  echo

 else
  echo
  echo "Incorrect Input....."
  echo
 fi
done
 rm -rf book1 .book1 fname .n1 n2 n1 n n3 n4 book2 book3 book4 error year1 year2

