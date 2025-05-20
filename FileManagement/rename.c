#include <stdio.h>

int main() {
    if (rename("myfile.txt", "newname.txt") == -1) {
        perror("rename");
        return 1;
    }
    return 0;
}
