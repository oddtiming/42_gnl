/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:06:59 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/10/21 11:57:58 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

/*	Reads to the static char *remain[fd] until a nl is found, or until
 *	the EOF has been reached. If read() reaches EOF (returns nbyte < BUFF_SIZE)	
 *	or attempts an invalid read () (returns -1) and remain[fd] doesn't
 *	end with \n, get_line_len() returns 0.
 */
static long	get_line_len(char **remain, int fd)
{
	long	read_status;
	char	*read_buf;

	while (!(*remain) || !strlen_c(*remain, '\n'))
	{
		read_buf = malloc(BUFFER_SIZE + 1);
		read_status = read(fd, read_buf, BUFFER_SIZE);
		if (read_status <= 0)
			return ((int) ft_free(read_buf));
		read_buf[read_status] = 0;
		*remain = ft_strjoin_free(*remain, read_buf);
		free(read_buf);
	}
	return (strlen_c(*remain, '\n'));
}

/*	NOTE: Max number of file descriptors on MacOS is 12288
 *	https://wilsonmar.github.io/maximum-limits/
 *	get_next_line_bonus is used to return the string content of MULTIPLE 
 *	input streams at a time, line by line. Every function call returns a line
 *	including the \n character.
 *	It uses static char *remain[fd] to store the excess buffer from the read()
 *	function (i.e. everything after \n). 
 *	The second if(!line_len) checks if remain[fd] is empty. The last if is
 *	facultative as it is merely there to ensure that free() happens as soon
 *	as the last line is hit.
 */
char	*get_next_line(int fd)
{
	char		*current_line;
	long		line_len;
	static char	*remain[12288];

	if (fd < 0 || fd >= 12288)
		return (NULL);
	line_len = get_line_len(&(remain[fd]), fd);
	if (!line_len)
		line_len = strlen_c(remain[fd], 0);
	if (!line_len)
	{
		remain[fd] = ft_free(remain[fd]);
		return (NULL);
	}
	current_line = malloc(line_len + 1);
	ft_strncpy(current_line, remain[fd], line_len);
	if (!strlen_c(remain[fd], '\n'))
		remain[fd] = ft_free(remain[fd]);
	else
		ft_strncpy(remain[fd], &remain[fd][line_len], \
			strlen_c(remain[fd], 0) - line_len + 1);
	return (current_line);
}
