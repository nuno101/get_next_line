#include <stdio.h>
#include "../get_next_line.c"
#include "../get_next_line_utils.c"
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	//const char filepath[] = "test/empty";
	const char filepath[] = "test/multiple_line_with_nl";
	//const char filepath[] = "test/file.txt";
	//const char filepath[] = "test/file2.txt";
	int fd;
	char *nl;
	int debug = 1;

	debug = 0;
	if (debug == 1)
	   	printf("opening file: %s\n", filepath);
	fd = open(filepath, O_RDONLY);
	if (debug == 1)
    	printf("file descriptor is: %d\n", fd);

	printf("%s", nl = get_next_line(fd));
	free(nl);
	printf("%s", nl = get_next_line(fd));
	free(nl);
	printf("%s", nl = get_next_line(fd));
	free(nl);
	printf("%s", nl = get_next_line(fd));
	free(nl);
	printf("%s", nl = get_next_line(fd));
	free(nl);
	printf("%s", nl = get_next_line(fd));
	free(nl);
    //printf("fd %d next  line:\n%s\n", fd, get_next_line(fd));

/*
	while ((nl = get_next_line(fd)))
	{
		if (debug == 1)
			printf("next line: %s", nl);
		else
		{
			//printf("%p\n", nl);
			printf("%s", nl);
		}
		free(nl);
	}
*/
	//if (debug == 1)
	//	if (nl == NULL)
    //		printf("last nl is NULL %s\n", nl); 
	// keep program runnig to check leaks
	getchar();
	return (0);
}
