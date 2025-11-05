#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "data.txt";
    const char *content = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const size_t content_len = strlen(content);
    const mode_t mode = 0644;
    
    int fd;
    ssize_t bytes_written;
    off_t file_size;

    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }
    
    bytes_written = write(fd, content, content_len);
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }
    
    if (bytes_written != content_len) {
        fprintf(stderr, "Partial write occurred\n");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("Error closing file after writing");
        return 1;
    }

    printf("Wrote %ld bytes to %s\n", bytes_written, filename);

    fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("Error reopening file with O_RDWR");
        return 1;
    }

    file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error seeking to end of file");
        close(fd);
        return 1;
    }
    
    printf("File size after write: %ld bytes\n", file_size);
    
    if (ftruncate(fd, 10) == -1) {
        perror("Error truncating file");
        close(fd);
        return 1;
    }
    
    printf("Truncated file to 10 bytes\n");

    file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error seeking to end of file");
        close(fd);
        return 1;
    }
    
    printf("New file size after truncate: %ld bytes\n", file_size);

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error seeking to start of file");
        close(fd);
        return 1;
    }

    char buffer[11];
    
    ssize_t bytes_read = read(fd, buffer, 10);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd);
        return 1;
    }
    
    buffer[bytes_read] = '\0';
    printf("Content remaining in file: \"%s\"\n", buffer);
    
    if (close(fd) == -1) {
        perror("Error closing file at the end");
        return 1;
    }
    
    return 0;
}
