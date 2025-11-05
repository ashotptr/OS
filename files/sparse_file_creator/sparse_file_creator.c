#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *filename = "sparse.bin";
    const mode_t mode = 0644;
    const char *start_str = "START";
    const char *end_str = "END";
    const off_t offset = 1024 * 1024;
    
    int fd;
    off_t file_size;

    printf("Creating '%s'...\n", filename);
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd == -1) {
        perror("Error opening file for writing");
        return 1;
    }
    if (write(fd, start_str, strlen(start_str)) == -1) {
        perror("Error writing 'START'");
        close(fd);
        return 1;
    }
    printf("Wrote '%s' to file.\n", start_str);
    
    if (lseek(fd, offset, SEEK_CUR) == -1) {
        perror("Error seeking in file");
        close(fd);
        return 1;
    }
    printf("Seeked forward %lld bytes.\n", (long long)offset);

    if (write(fd, end_str, strlen(end_str)) == -1) {
        perror("Error writing 'END'");
        close(fd);
        return 1;
    }
    printf("Wrote '%s' to file.\n", end_str);

    if (close(fd) == -1) {
        perror("Error closing file after writing");
        return 1;
    }
    printf("Sparse file created.\n\n");

    printf("Re-opening file to check size...\n");
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        return 1;
    }
    
    file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error seeking to end of file");
        close(fd);
        return 1;
    }

    printf("Apparent file size (from lseek): %lld bytes.\n", (long long)file_size);

    close(fd);

    return 0;
}
