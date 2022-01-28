#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int main()
{
    int fd;
    char *buf;

    fd = open("TextToRead", O_RDONLY);
    read(fd, buf, 10);
    printf("%s---", buf);
    read(fd, buf, 10);
    printf("%s---", buf);
    return (0);
}