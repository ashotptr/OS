#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define INPUT_BUFFER_SIZE 1024

int int_to_str(int n, char* buffer) {
    if (n == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return 1;
    }

    int i = 0;
    
    while (n != 0) {
        buffer[i] = (n % 10) + '0';
        n = n / 10;
        i++;
    }

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    buffer[i] = '\0';
    return i;
}


int main() {
    const char *filename = "log.txt";
    const mode_t mode = 0644;
    int fd;
    
    char input_buffer[INPUT_BUFFER_SIZE];
    char pid_prefix_buffer[64];
    char pid_str_buffer[32];
    
    ssize_t bytes_read, bytes_written;
    off_t final_offset;

    fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, mode);
    if (fd == -1) {
        perror("Error opening log.txt");
        return 1;
    }

    printf("Enter log line: ");
    fflush(stdout); 
    
    bytes_read = read(STDIN_FILENO, input_buffer, sizeof(input_buffer));
    if (bytes_read == -1) {
        perror("Error reading from standard input");
        close(fd);
        return 1;
    }
    
    if (bytes_read == 0) {
        printf("No input provided.\n");
        close(fd);
        return 0;
    }

    pid_t pid = getpid();
    int pid_len = int_to_str(pid, pid_str_buffer);
    int prefix_len = 0;

    pid_prefix_buffer[0] = 'P';
    pid_prefix_buffer[1] = 'I';
    pid_prefix_buffer[2] = 'D';
    pid_prefix_buffer[3] = '=';
    prefix_len = 4;

    int i;
    for (i = 0; i < pid_len; i++) {
        pid_prefix_buffer[prefix_len + i] = pid_str_buffer[i];
    }
    prefix_len += pid_len;

    pid_prefix_buffer[prefix_len] = ':';
    pid_prefix_buffer[prefix_len + 1] = ' ';
    prefix_len += 2;

    bytes_written = write(fd, pid_prefix_buffer, prefix_len);
    if (bytes_written == -1) {
        perror("Error writing PID prefix");
        close(fd);
        return 1;
    }

    bytes_written = write(fd, input_buffer, bytes_read);
    if (bytes_written == -1) {
        perror("Error writing log message");
        close(fd);
        return 1;
    }

    if (bytes_read > 0 && input_buffer[bytes_read - 1] != '\n') {
        if (write(fd, "\n", 1) == -1) {
            perror("Error writing final newline");
            close(fd);
            return 1;
        }
    }

    final_offset = lseek(fd, 0, SEEK_CUR);
    if (final_offset == -1) {
        perror("Error getting final file offset");
        close(fd);
        return 1;
    }

    printf("Successfully wrote log. New file offset: %lld\n", (long long)final_offset);

    if (close(fd) == -1) {
        perror("Error closing log file");
        return 1;
    }

    return 0;
}

//With the O_APPEND option, when writing to a file, we always start at the end, and the file pointer is positioned at the end, when we complete the write operation, the file pointer appears at the end of the file. 
//Hence, when using SEEK_CUR, it returns the size to the end of the file in bytes.
