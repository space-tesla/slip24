/*Print the type of file and inode number where the filename is accepted through the command line.*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;
    if (stat(argv[1], &fileStat) == 0) {
        printf("File: %s\n", argv[1]);
        printf("Inode: %ld\n", fileStat.st_ino);
        
        if (S_ISREG(fileStat.st_mode)) printf("Type: Regular File\n");
        else if (S_ISDIR(fileStat.st_mode)) printf("Type: Directory\n");
        else if (S_ISCHR(fileStat.st_mode)) printf("Type: Character Device\n");
        else if (S_ISBLK(fileStat.st_mode)) printf("Type: Block Device\n");
        else if (S_ISFIFO(fileStat.st_mode)) printf("Type: FIFO or Pipe\n");
        else if (S_ISLNK(fileStat.st_mode)) printf("Type: Symbolic Link\n");
        else if (S_ISSOCK(fileStat.st_mode)) printf("Type: Socket\n");
        else printf("Type: Unknown\n");
    } else {
        printf("Cannot access file: %s\n", argv[1]);
    }

    return 0;
}


/*$ ./a.out example.txt
File: example.txt
Inode: 1234567
Type: Regular File
*/