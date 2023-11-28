/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:10 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/28 17:24:46 by deydoux          ###   ########.fr       */
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

static char	*create_line(int fd, char *stash, size_t line_len)
{
	ssize_t	buffer_len;
	char	*buffer;
	char	*line;

	buffer_len = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	line = NULL;
	if (!buffer)
		return (NULL);
	if (!line_len)
		buffer_len = read_stash(stash, buffer);
	if (!buffer_len)
		buffer_len = read(fd, buffer, BUFFER_SIZE);
	if (buffer_len <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[buffer_len] = 0;
	buffer_len = 0;
	while (buffer[buffer_len] && buffer[buffer_len] != '\n')
		buffer_len++;
	buffer_len += buffer[buffer_len] == '\n';
	if (buffer[buffer_len - 1] != '\n')
		line = create_line(fd, stash, line_len + buffer_len);
	if (!line)
	{
		ft_memcpy(stash, buffer, BUFFER_SIZE);
		line = malloc(sizeof(char) * (line_len + buffer_len + 1));
		if (line)
			line[line_len + buffer_len] = 0;
	}
	if (line)
		ft_memcpy(line + line_len, buffer, buffer_len);
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];

	if (fd < 1 || BUFFER_SIZE < 1)
		return (NULL);
	return (create_line(fd, stash, 0));
}
