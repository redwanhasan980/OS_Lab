#include <unistd.h>

int main() {
    if (unlink("myfile.txt") == -1) {
        perror("unlink");
        return 1;
    }
    return 0;
}
