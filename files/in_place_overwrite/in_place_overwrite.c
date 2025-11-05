#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char* FILENAME = "numbers.txt";
    const mode_t MODE = 0644;
    
    int fd;
    char line_buffer[16];
    ssize_t bytes_written;
    size_t total_written;
    
    printf("Creating %s with numbers 1-10.\n", FILENAME);
    fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, MODE);
    if (fd == -1) {
        perror("Error creating initial file");
        return 1;
    }
    
    for (int i = 1; i <= 10; i++) {
        int line_len = snprintf(line_buffer, sizeof(line_buffer), "%d\n", i);
        
        total_written = 0;
        while (total_written < line_len) {
            bytes_written = write(fd, line_buffer + total_written, line_len - total_written);
            
            if (bytes_written == -1) {
                perror("Error writing initial file");
                close(fd);
                return 1;
            }

            total_written += bytes_written;
        }
    }
    close(fd);

    printf("Re-opening file with O_RDWR.\n");
    fd = open(FILENAME, O_RDWR);
    if (fd == -1) {
        perror("Error re-opening file");
        return 1;
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error getting file size");
        close(fd);
        return 1;
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error rewinding file");
        close(fd);
        return 1;
    }

    off_t line_start_offset = 0;
    int newline_count = 0;
    char c;
    
    while (read(fd, &c, 1) > 0) {
        if (c == '\n') {
            newline_count++;
            if (newline_count == 3) {
                break;
            }
        }
    }
    
    line_start_offset = lseek(fd, 0, SEEK_CUR);
    if (line_start_offset == -1) {
        perror("Error finding line offset");
        close(fd);
        return 1;
    }
    printf("Found offset of line 4: %lld\n", (long long)line_start_offset);

    int old_line_len = 0;
    while (read(fd, &c, 1) > 0) {
        old_line_len++;
        if (c == '\n') {
            break;
        }
    }

    off_t remainder_start_offset = line_start_offset + old_line_len;
    ssize_t remainder_size = file_size - remainder_start_offset;
    char* remainder_buffer = NULL;

    printf("Old line length is %d, remainder is %zd bytes.\n", old_line_len, remainder_size);

    if (remainder_size > 0) {
        remainder_buffer = (char*)malloc(remainder_size);
        if (remainder_buffer == NULL) {
            perror("Error allocating memory for remainder");
            close(fd);
            return 1;
        }
        
        lseek(fd, remainder_start_offset, SEEK_SET);
        
        ssize_t bytes_read = read(fd, remainder_buffer, remainder_size);
        if (bytes_read != remainder_size) {
            perror("Error reading remainder of file");
            free(remainder_buffer);
            close(fd);
            return 1;
        }
        printf("Read remainder into memory.\n");
    }

    lseek(fd, line_start_offset, SEEK_SET);

    const char* new_line = "100\n";
    int new_line_len = strlen(new_line);
    
    total_written = 0;
    while (total_written < new_line_len) {
        bytes_written = write(fd, new_line + total_written, new_line_len - total_written);
        
        if (bytes_written == -1) {
            perror("Error writing new line");
            free(remainder_buffer);
            close(fd);
            return 1;
        }
        total_written += bytes_written;
    }
    
    printf("Wrote new line '100\\n' at offset %lld.\n", (long long)line_start_offset);


    if (remainder_size > 0) {
        total_written = 0;
        while (total_written < remainder_size) {
            bytes_written = write(fd, remainder_buffer + total_written, remainder_size - total_written);
            
            if (bytes_written == -1) {
                perror("Error writing remainder");
                free(remainder_buffer);
                close(fd);
                return 1;
            }
            total_written += bytes_written;
        }
        
        free(remainder_buffer);
        printf("Wrote remainder back to file.\n");
    }
    
    off_t new_file_size = line_start_offset + new_line_len + remainder_size;
    if (ftruncate(fd, new_file_size) == -1) {
        perror("Error truncating file to final size");
        close(fd);
        return 1;
    }

    close(fd);
    printf("Overwrite complete.\n");

    printf("\n--- Verifying content of '%s' ---\n", FILENAME);
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for verification");
        return 1;
    }
    
    char verify_buffer[1024];
    ssize_t bytes_read;
    
    while ((bytes_read = read(fd, verify_buffer, sizeof(verify_buffer))) > 0) {
        if (write(STDOUT_FILENO, verify_buffer, bytes_read) == -1) {
            perror("Error writing to stdout");
            close(fd);
            return 1;
        }
    }
    printf("--- End of file ---\n");
    
    close(fd);
    
    if (bytes_read == -1) {
        perror("Error reading file for verification");
        return 1;
    }
    
    return 0;
}
