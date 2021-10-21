/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:10:14 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/27 18:09:41 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	strlen_nl(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\n' && s[i])
	{
		i++;
	}
	if (s[i] != '\n')
		return (0);
	else
		return (i + 1);
}

static long	get_line_len(char **remain, int fd)
{
	long	read_status;
	char	*read_buf;

	while (!(*remain) || !strlen_nl(*remain))
	{
		read_buf = malloc(BUFFER_SIZE + 1);
		read_status = read(fd, read_buf, BUFFER_SIZE);
		if (read_status < BUFFER_SIZE)
		{
			if (read_status <= 0)
			{
				free (read_buf);
				return (read_status);
			}
			read_buf[read_status] = 0;
		}
		else
			read_buf[BUFFER_SIZE] = 0;
		*remain = ft_strjoin(*remain, read_buf);
		free(read_buf);
		if (read_status < BUFFER_SIZE)
			return (0);
	}
	return (strlen_nl(*remain));
}

static void	*ft_memclear(void *element)
{
	free(element);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*current_line;
	long		line_len;
	static char	*remain = NULL;

	line_len = get_line_len(&remain, fd);
	if (line_len <= 0)
	{
		if (line_len == -1)
			return (ft_memclear(remain));
		line_len = strlen_nl(remain);
		if (!line_len)
			line_len = ft_strlen(remain);
		if (!line_len)
			return (ft_memclear(remain));
	}
	current_line = malloc(line_len + 1);
	ft_strncpy(current_line, remain, line_len);
	ft_memmove(remain, &remain[line_len], ft_strlen(remain) - line_len + 1);
	return (current_line);
}
