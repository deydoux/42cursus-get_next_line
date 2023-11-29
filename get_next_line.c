/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:10 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/29 14:02:33 by deydoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	read_stash(char *stash, char *buffer)
{
	size_t	start;
	size_t	len;

	start = 0;
	len = 0;
	while (stash[start] && stash[start] != '\n')
		start++;
	if (stash[start++] == '\n')
	{
		while (stash[start + len])
		{
			buffer[len] = stash[start + len];
			len++;
		}
	}
	return (len);
}

static char	*init_buffer(char *stash, int fd, int *error, int stash_readed)
{
	char	*buffer;
	ssize_t	len;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		*error = 1;
		return (NULL);
	}
	len = 0;
	if (!stash_readed)
		len = read_stash(stash, buffer);
	if (!len)
		len = read(fd, buffer, BUFFER_SIZE);
	*error = len < 0;
	if (!len || *error)
	{
		free(buffer);
		return (NULL);
	}
	buffer[len] = 0;
	return (buffer);
}

static char	*init_line(size_t size, char *buffer, char *stash, int *error)
{
	char	*line;

	ft_memcpy(stash, buffer, BUFFER_SIZE);
	line = malloc(sizeof(char) * (size + 1));
	if (line)
		line[size] = 0;
	else
		*error = 1;
	return (line);
}

static char	*create_line(int fd, char *stash, int *error, size_t line_len)
{
	char	*buffer;
	char	*line;
	size_t	buffer_len;

	buffer = init_buffer(stash, fd, error, line_len != 0);
	if (!buffer)
		return (NULL);
	line = NULL;
	buffer_len = 0;
	while (buffer[buffer_len] && buffer[buffer_len] != '\n')
		buffer_len++;
	buffer_len += buffer[buffer_len] == '\n';
	if (buffer[buffer_len - 1] != '\n')
		line = create_line(fd, stash, error, line_len + buffer_len);
	if (!line && !*error)
		line = init_line(line_len + buffer_len, buffer, stash, error);
	if (line)
		ft_memcpy(line + line_len, buffer, buffer_len);
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	int			error;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	error = 0;
	line = create_line(fd, stash, &error, 0);
	if (error)
		ft_bzero(stash, sizeof(stash));
	return (line);
}
