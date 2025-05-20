#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int source = open("myfile.txt", O_RDONLY);
    if (source == -1) { perror("open source"); return 1; }

    int dest = open("dest.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (dest == -1) { perror("open dest"); return 1; }

    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(source, buffer, sizeof(buffer))) > 0) {
        write(dest, buffer, bytes);
    }

    close(source);
    close(dest);
    return 0;
}
