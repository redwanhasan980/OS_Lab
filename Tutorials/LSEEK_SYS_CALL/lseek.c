//lseek is used to reposition the file offset of the open file descriptor.
// The file offset is the position in the file where the next read or write operation will occur.
//off_t lseek(int fd, off_t offset, int whence)
//fd: The file descriptor of the open file.
//offset: The number of bytes to offset the file position.
//whence: The starting point for the offset. It can be one of the following values:
//SEEK_SET: The offset is set to offset bytes from the beginning of the file.
//SEEK_CUR: The offset is set to the current file position plus offset bytes.
//SEEK_END: The offset is set to the size of the file plus offset bytes.
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
int main(){
    int n,f,f1;
    char buf[100];
    f=open("test.txt",O_RDWR);//1234567890abcdefghijx1x2x3x4x5
    write(f,"1234567890abcdefghijx1x2x3x4x5",30);
    //at this point pointer is at 30
     lseek(f, 0, SEEK_SET); // Move the file offset to the beginning of the file
    read(f,buf,10);
    // at this point pointer is at 10 where a is 
    write(1,buf,10);
    lseek(f,10,SEEK_CUR); // Move the file offset to 10 bytes from the current position
    read(f,buf,10); // Read 10 bytes from the file
    write(1,buf,10); // Write the read bytes to standard output
    

}