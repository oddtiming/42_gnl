/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_w_temp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 13:10:14 by iyahoui-          #+#    #+#             */
/*   Updated: 2021/09/27 16:36:33 by iyahoui-         ###   ########.fr       */
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

static long	get_line_len(char **remainder, int fd)
{
	long	read_status;
	char	*read_buf;

	while (!(*remainder) || !strlen_nl(*remainder))
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
		*remainder = ft_strjoin(*remainder, read_buf);
		free(read_buf);
		if (read_status < BUFFER_SIZE)
			return (0);
	}
	return (strlen_nl(*remainder));
}

static void	*ft_memclear(void *element)
{
	free(element);
	return (NULL);
}

//Fct is two lines too long.
//Could easily add a memclear function that returns NULL to save 6 lines
//e.g. static void *ft_memclear(void *element) {free(element); return (NULL);} 
//Could also incorporate malloc + free in strcpy + strncpy to save 4 lines
//Could also incorporate line_len tree inside get_line_len fct
char	*get_next_line(int fd)
{
	char		*current_line;
	long		line_len;
	static char	*remainder = NULL;
	char		*temp_ptr;

	line_len = get_line_len(&remainder, fd);
	if (line_len <= 0)
	{
		if (line_len == -1)
			return (ft_memclear(remainder));
		line_len = strlen_nl(remainder);
		if (!line_len)
			line_len = ft_strlen(remainder);
		if (!line_len)
			return (ft_memclear(remainder));
	}
	current_line = malloc(line_len + 1);
	ft_strncpy(current_line, remainder, line_len);
	temp_ptr = remainder;
	remainder = malloc(ft_strlen(temp_ptr) - line_len + 1);
	ft_strcpy(remainder, &temp_ptr[line_len]);
	free (temp_ptr);
	return (current_line);
}
