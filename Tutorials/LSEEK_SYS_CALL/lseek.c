//lseek is used to reposition the file offset of the open file descriptor.
// The file offset is the position in the file where the next read or write operation will occur.
//off_t lseek(int fd, off_t offset, int whence)
//fd: The file descriptor of the open file.
//offset: The number of bytes to offset the file position.
//whence: The starting point for the offset. It can be one of the following values:
//SEEK_SET: The offset is set to offset bytes from the beginning of the file.
//SEEK_CUR: The offset is set to the current file position plus offset bytes.
//SEEK_END: The offset is set to the size of the file plus offset bytes.