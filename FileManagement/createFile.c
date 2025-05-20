#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("myfile.txt", O_CREAT | O_WRONLY, 0644);  // rw-r--r--
    if (fd == -1) {
        perror("create");
        return 1;
    }
    write(fd, "Hello, Linux!\n", 14);
    close(fd);
    return 0;
}
