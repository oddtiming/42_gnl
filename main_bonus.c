#include "get_next_line_bonus.h"
#include <string.h>
#include <stdio.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

int	main(void)
{
	int		fd1, fd2, fd3;
	int		status;
	char	*ptr1, *ptr2, *ptr3;
	char	*file1 = "./test_files/test_nl.txt";
	char	*file2 = "./test_files/test_short_nonl.txt";
	char	*file3 = "./test_files/test_long_nonl.txt";
	int 	line_count = 0;


	fd1 = open(file1, O_RDONLY);
	fd2 = open(file2, O_RDONLY);
	fd3 = open(file3, O_RDONLY);

	puts("---------STARTING TESTS MULTIPLE FDs---------\n\n");
	printf("File 1 = %s\n", file1);
	printf("File 2 = %s\n", file2);
	printf("File 1 = %s\n", file3);
	printf("Fd1 = %d\nFd2 = %d\nFd3 = %d\nbuff_size = %d\n\n", fd1, fd2, fd3, BUFFER_SIZE);
	ptr1 = get_next_line(fd1);
	ptr2 = get_next_line(fd2);
	ptr3 = get_next_line(fd3);
	int fd_error = -1;

	while (ptr1 || ptr2 || ptr3)
	{
	
		line_count++;
		/*
		printf("Line #%d for file #1 ==> %s\n",line_count, ptr1);
		printf("Line #%d for file #2 ==> %s\n",line_count, ptr2);
		printf("Line #%d for file #3 ==> %s\n",line_count, ptr3);
		*/

		if (ptr1)
		{
			printf("Line #%d for file #1 ==> %s\n",line_count, ptr1);
			free (ptr1);
		}
		if (ptr2)
		{
			printf("Line #%d for file #2 ==> %s\n",line_count, ptr2);
			free (ptr2);
		}
		if (ptr3)
		{
			printf("Line #%d for file #3 ==> %s\n",line_count, ptr3);
			free (ptr3);
		}
	 
		ptr1 = get_next_line(fd1);
		ptr2 = get_next_line(fd2);
		ptr3 = get_next_line(fd3);
		get_next_line(fd_error);

	}

	status = close(fd1);
	status = close(fd2);
	status = close(fd3);
}
