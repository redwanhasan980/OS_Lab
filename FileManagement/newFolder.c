#include <sys/stat.h>
#include <sys/types.h>

int main() {
    if (mkdir("newDir", 0755) == -1) {//0755 is the permission for the directory
                                   // 0755 means the owner can read, write and execute, group can read and execute, others can read and execute
        perror("mkdir");
        return 1;
    }
    return 0;
}
