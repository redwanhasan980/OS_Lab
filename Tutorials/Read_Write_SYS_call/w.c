#include<unistd.h>
#include<stdio.h>
int main(){
write(1,"Hello\n",6);
write(1,"Hello\n",2);
int n=write(1,"Hello\n",6);
printf("%d\n",n);
return 0;
}
//Comment out: This program uses the write system call to print "Hello" to the standard output (file descriptor 1).
// The write function takes three arguments: the file descriptor, a pointer to the data to write, and the number of bytes to write.
// In this case, it writes 5 bytes from the string "Hello" to the standard output.

