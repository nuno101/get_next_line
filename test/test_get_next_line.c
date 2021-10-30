#include <stdio.h>
#include "../get_next_line.c"
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	const char filepath[] = "test/file.txt";
	int fd;
	//char *nl;
    printf("get_next_line called w/ BUFFER_SIZE = %d\n", BUFFER_SIZE);

    printf("opening file: %s\n", filepath);
	fd = open(filepath, O_RDONLY);
    printf("file descriptor is: %d\n", fd);

    printf("fd %d first line:\n%s\n", fd, get_next_line(fd));
    printf("fd %d next  line:\n%s\n", fd, get_next_line(fd));
    printf("fd %d next  line:\n%s\n", fd, get_next_line(fd));
    printf("fd %d next  line:\n%s\n", fd, get_next_line(fd));

	//nl = get_next_line(fd);
    //printf("fd second line:\n%s\n", nl); 

	return (0);
}
