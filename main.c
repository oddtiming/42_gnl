#include "get_next_line.h"
#include <string.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

int	main(void)
{
	int		fd;
	int		status;
	char	*ptr;
	char	*file1 = "./test_files/test_nl.txt";
	char	*file2 = "./test_files/test_short_nonl.txt";
	char	*file3 = "./test_files/test_long_nonl.txt";


	fd = open(file1, O_RDONLY);
	puts("---------STARTING TESTS NL---------\n\n");
	printf("File 1 = %s\n", file1);
	printf("Fd = %d\nbuff_size = %d\n", fd, BUFFER_SIZE);
	while ((ptr = get_next_line(fd)))
	{
		printf("Line ==> %s\n", ptr);
		free (ptr);
	}
	status = close(fd);


	fd = open(file2, O_RDONLY);
	puts("---------STARTING TESTS SHORT NO NL---------\n\n");
	printf("File 2 = %s\n", file2);
	printf("Fd = %d\nbuff_size = %d\n", fd, BUFFER_SIZE);
	while ((ptr = get_next_line(fd)))
	{
		printf("Line ==> %s\n", ptr);
		free (ptr);
	}
	status = close(fd);


	fd = open(file3, O_RDONLY);
	puts("---------STARTING TESTS LONG NO NL---------\n\n");
	printf("File 1 = %s\n", file3);
	printf("Fd = %d\nbuff_size = %d\n", fd, BUFFER_SIZE);
	while ((ptr = get_next_line(fd)))
	{
		printf("Line ==> %s\n", ptr);
		free (ptr);
	}
	status = close(fd);

}
