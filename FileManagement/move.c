#include <stdio.h>

int main() {
    const char *source = "/home/redwan/OS_Lab/FileManagement/myfile.txt";
    // Use the full path to the source file
    const char *destination = "/home/redwan/OS_Lab/FileManagement/newDir/myfile.txt";
    // Use the full path to the destination file

    if (rename(source, destination) == -1) {
        perror("rename");
        return 1;
    }

    printf("File moved successfully!\n");
    return 0;
}
