#!/bin/sh
# This is a comment!
echo Hello World        # This is a comment, too!
echo  "Hello      World"    "me"   # This is a comment, too!
echo "Hello      World"       # This is a comment, too!
echo "Hello World"
echo "Hello * World"
#Var
MY_MESSAGE="Hello Key"
echo $MY_MESSAGE
MY_MESSAGE="Hello World"
MY_SHORT_MESSAGE=hi
MY_NUMBER=1
MY_PI=3.142
MY_OTHER_PI="3.142"
MY_MIXED=123abc
echo $MY_MESSAGE
echo What is your name?
#read MY_NAME
echo "Hello $MY_NAME - hope you're well."

#Scope of Var
echo "MYVAR is: $MYVAR"
MYVAR="hi there"
echo "MYVAR is: $MYVAR"

echo "What is your name?"
read USER_NAME
echo "Hello $USER_NAME"
echo "I will create you a file called ${USER_NAME}_file"
touch "${USER_NAME}_file.txt"
echo /home/$USER_NAME/OS_Lab/Sheel_Scripting/*