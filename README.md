# get_next_line

A C function that returns a line read from a file descriptor, developed as part of the 42 School curriculum. The function can handle reading from files, standard input, or any other file descriptor, one line at a time.

## About the project

`get_next_line` is an implementation of a function that reads content line by line from a file descriptor. This project introduces important programming concepts such as static variables, file manipulation, memory allocation, and buffer handling in C.

### Key Features

- Reads from multiple file descriptors without losing track of each reading's progress
- Handles variable buffer sizes defined at compilation time
- Efficient memory management with no leaks
- Works with both files and standard input
- Handles lines with or without newline characters
- Follows 42 School's strict coding standards

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: The file descriptor to read from

### Return Value
- Returns the line that was read (including the terminating `\n` character if present)
- Returns NULL if there is nothing else to read or if an error occurred

## Technical Details

### Function Behavior

- Reads the file line by line
- Returns the full line including the terminating newline character (`\n`)
- Returns the line without newline if it's the last line and doesn't end with a newline
- Returns NULL when reaching EOF or on error
- Uses a static variable to keep track of remaining content between function calls

### Compilation

The project must be compiled with the following flags:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=xx files.c
```
where `xx` can be any positive integer value.

### Project Structure

- `get_next_line.c`: Main function implementation
- `get_next_line.h`: Header file with function prototypes and includes
- `get_next_line_utils.c`: Helper functions implementation

### Memory Management

The project follows strict memory management rules:
- All allocated memory must be properly freed
- No memory leaks are allowed
- Uses only allowed functions: `read`, `malloc`, and `free`

## Coding Standards

This project follows 42 School's strict coding standard ("The Norm"), which includes:

- Maximum 25 lines per function
- Maximum 80 characters per line
- Maximum 5 functions per file
- Variable declarations must be at the start of functions
- Variable declaration and assignment must be on separate lines
- Only certain specific loop and condition structures are allowed

Note: While modern IDEs might suggest optimizations or improvements that violate these standards, the code must strictly adhere to the school's norm as part of the learning process.

## Usage Example

```c
int main()
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
