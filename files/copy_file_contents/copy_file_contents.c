#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define BUFFER_SIZE 4096

void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int main() {
    char source_path[256];
    char dest_path[256];
    int fd_source, fd_dest;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    long long total_bytes_copied = 0;

    mode_t mode = 0644;

    printf("Enter the source file path: ");
    if (fgets(source_path, sizeof(source_path), stdin) == NULL) {
        fprintf(stderr, "Error reading source path\n");
        return 1;
    }
    remove_newline(source_path);

    printf("Enter the destination file path: ");
    if (fgets(dest_path, sizeof(dest_path), stdin) == NULL) {
        fprintf(stderr, "Error reading destination path\n");
        return 1;
    }
    remove_newline(dest_path);

    fd_source = open(source_path, O_RDONLY);
    if (fd_source == -1) {
        perror("Error opening source file");
        return 1;
    }

    fd_dest = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, mode);
    if (fd_dest == -1) {
        perror("Error opening/creating destination file");
        close(fd_source);
        return 1;
    }

    while ((bytes_read = read(fd_source, buffer, BUFFER_SIZE)) > 0) {
        ssize_t total_written_for_chunk = 0;

        while (total_written_for_chunk < bytes_read) {
            bytes_written = write(fd_dest, buffer + total_written_for_chunk, bytes_read - total_written_for_chunk);

            if (bytes_written == -1) {
                perror("Error writing to destination file");
                close(fd_source);
                close(fd_dest);
                return 1;
            }

            total_written_for_chunk += bytes_written;
        }

        total_bytes_copied += total_written_for_chunk;
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
        close(fd_source);
        close(fd_dest);
        return 1;
    }

    if (close(fd_source) == -1) {
        perror("Error closing source file");
        close(fd_dest);
        return 1;
    }

    if (close(fd_dest) == -1) {
        perror("Error closing destination file");
        return 1;
    }

    printf("Successfully copied %lld bytes.\n", total_bytes_copied);

    return 0;
}
