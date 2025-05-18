// man 2 open 
// to see the manual page for the open system call.
//open(const char *pathname, int flags);
// *pathname: The name of the file to open.
// *flags: The access mode write or read
//open(char *pathname, int flags , mode_t mode);
// *mode: The permissions to set for the file if it is created.
// The open system call is used to open a file and obtain a file descriptor for it.
// The file descriptor can then be used with other system calls, such as read and write, to perform I/O operations on the file.
// The open system call returns a file descriptor, which is a non-negative integer that represents the opened file.
// If the open call fails, it returns -1 and sets the global variable errno to indicate the error.
// The open system call can be used to open files in different modes, such as read-only, write-only, or read-write.
#include<fcntl.h> // <fcntl.h> is used for file control options
#include<unistd.h> 
#include<stdio.h>
#include<sys/types.h>// <sys/types.h> is used for data types used in system calls
#include<sys/stat.h> // <sys/stat.h> is used for file status information
int main(){
    int n,fd;
    char buffer[30];
    fd=open("test.txt",O_RDONLY); // Open the file "test.txt" in read-only mode
    //fd contains the file descriptor for the opened file
    n=read(0,buffer,30); // Read up to 30 bytes from the file into the buffer
    write(1,buffer,n); // Write the read bytes to standard output (file descriptor 1). file descriptor 1 means standard output
    // fd 1 shows in the shell
   int fd1= open("terget.txt",O_CREAT|O_WRONLY|O_APPEND,0642); // Open the file "terget.txt" in create and write-only mode
    // O_CREAT: Create the file if it does not exist
    // O_WRONLY: Open the file for writing only
    // 0642: Set the file permissions to read and write for the owner, and read for the group and others
    write(fd1,buffer,n); // Write the read bytes to the file "terget.txt"
}
