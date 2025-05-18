#include<unistd.h>
#include<stdio.h>
int main(){
    char buffer[30];
    int n = read(0, buffer,30); // Read up to 100 bytes from standard input (file descriptor 0)
    write(1, buffer, n); // Write the read bytes to standard output (file descriptor 1)
    return 0;
}
// Read return total number of bytes read
// Write return total number of bytes written
// The read function reads data from a file descriptor into a buffer.
// The write function writes data from a buffer to a file descriptor.
// if more than buffer size is read, it will be go into the shell as command 
