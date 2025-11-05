#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void remove_newline(char *str) {
    if (str == NULL) {
        return;
    }

    if (*str == '\0') {
        return;
    }

    char *end = str;
    while (*end != '\0') {
        end++;
    }

    end--;

    if (*end == '\n') {
        *end = '\0';
    }
}

int main() {
    char path[256];
    int fd;
    off_t file_size;
    off_t i;
    char buffer[1];

    printf("Enter the file path: ");
    if (fgets(path, sizeof(path), stdin) == NULL) {
        fprintf(stderr, "Error reading path\n");
        return 1;
    }
    remove_newline(path);
    
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error getting file size");
        close(fd);
        return 1;
    }

    for (i = file_size - 1; i >= 0; i--) {
        if (lseek(fd, i, SEEK_SET) == -1) {
            perror("Error seeking in file");
            close(fd);
            return 1;
        }

        ssize_t bytes_read = read(fd, buffer, 1);
        if (bytes_read == -1) {
            perror("Error reading byte");
            close(fd);
            return 1;
        }

        if (write(STDOUT_FILENO, buffer, 1) == -1) {
            perror("Error writing to standard output");
            close(fd);
            return 1;
        }
    }

    write(STDOUT_FILENO, "\n", 1);
    
    close(fd);
    return 0;
}
