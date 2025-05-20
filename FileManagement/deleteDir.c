#include <unistd.h>

int main() {
    if (rmdir("newDir") == -1) {
        perror("newDir");
        // If the directory is not empty, rmdir will fail
        // If you want to remove a non-empty directory, you can use the following command:
        // rm -r newDir
        // But be careful, as this will remove all files and subdirectories in newDir
        // and the directory itself.
        return 1;
    }
    return 0;
}
