#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 4096

void remove_newline(char *str) {
    if (str == NULL) {
	return;
    }
    size_t len = strlen(str);
    if (len == 0 || str[len - 1] != '\n') {
        return;
    }
    str[len - 1] = '\0';
}

int main() {
    char path1[256];
    char path2[256];
    int fd1, fd2;
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    ssize_t bytes_read1, bytes_read2;
    long long total_bytes_compared = 0;
    
    printf("Enter the first file path: ");
    if (fgets(path1, sizeof(path1), stdin) == NULL) {
        fprintf(stderr, "Error reading path 1\n");
        return 1;
    }
    remove_newline(path1);

    printf("Enter the second file path: ");
    if (fgets(path2, sizeof(path2), stdin) == NULL) {
        fprintf(stderr, "Error reading path 2\n");
        return 1;
    }
    remove_newline(path2);
    
    fd1 = open(path1, O_RDONLY);
    if (fd1 == -1) {
        perror("Error opening first file");
        return 1;
    }

    fd2 = open(path2, O_RDONLY);
    if (fd2 == -1) {
        perror("Error opening second file");
        close(fd1);
        return 1;
    }
    
    while (1) {
        bytes_read1 = read(fd1, buffer1, BUFFER_SIZE);
        if (bytes_read1 == -1) {
            perror("Error reading from first file");
            close(fd1);
            close(fd2);
            return 1;
        }

        bytes_read2 = read(fd2, buffer2, BUFFER_SIZE);
        if (bytes_read2 == -1) {
            perror("Error reading from second file");
            close(fd1);
            close(fd2);
            return 1;
        }

        ssize_t len_to_compare = (bytes_read1 < bytes_read2) ? bytes_read1 : bytes_read2;

        for (int i = 0; i < len_to_compare; i++) {
            if (buffer1[i] != buffer2[i]) {
                printf("Files differ at byte %lld\n", total_bytes_compared + i);
                close(fd1);
                close(fd2);
                exit(1);
            }
        }
        
        total_bytes_compared += len_to_compare;

        if (bytes_read1 != bytes_read2) {
            printf("Files differ at byte %lld\n", total_bytes_compared);
            close(fd1);
            close(fd2);
            exit(1);
        }

        if (bytes_read1 == 0) {
            break;
        }
    }

    printf("Files are identical\n");
    close(fd1);
    close(fd2);
    
    return 0;
}
