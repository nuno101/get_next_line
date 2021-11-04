#include <stdio.h>
#include "../get_next_line.c"
#include "../get_next_line_utils.c"
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	//const char filepath[] = "test/empty";
	const char filepath[] = "test/file.txt";
	int fd;
	char *nl;
/*
	char *buffer = "b";
	char *temp = "c";
	buffer = ft_strjoin(buffer, temp);
    printf("buffer: %s\n", buffer);
    printf("buffer: %p\n", buffer);
    printf("temp: %p\n", temp);
	buffer = temp;
    printf("buffer: %p\n", buffer);
    printf("temp: %p\n", temp);
	*temp = 'a';
    printf("temp: %p\n", temp);
	exit(0);
    printf("get_next_line called w/ BUFFER_SIZE = %d\n", BUFFER_SIZE);
*/
    printf("opening file: %s\n", filepath);
	fd = open(filepath, O_RDONLY);
    printf("file descriptor is: %d\n", fd);

/*
	printf("next line: %s\n", nl = get_next_line(fd));
	printf("next line: %s\n", nl = get_next_line(fd));

    printf("fd %d first line:\n%s\n", fd, get_next_line(fd));
    printf("fd %d next  line:\n%s\n", fd, get_next_line(fd));

*/
	while ((nl = get_next_line(fd)))
		printf("next line: %s\n", nl);
	if (nl == NULL)
    	printf("last nl is NULL %s\n", nl); 

	return (0);
}
