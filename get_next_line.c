/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:10 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/27 13:06:59 by deydoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	init_buffer(char *buffer, char *stash)
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

static char	*create_line(int fd, char *stash, size_t size)
{
	ssize_t	len;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;

	len = 0;
	line = NULL;
	if (!size)
		len = init_buffer(buffer, stash);
	if (!len)
		len = read(fd, buffer, BUFFER_SIZE);
	if (len <= 0)
		return (NULL);
	buffer[len] = 0;
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	len += buffer[len] == '\n';
	if (buffer[len - 1] != '\n')
		line = create_line(fd, stash, size + len);
	if (!line)
	{
		ft_memcpy(stash, buffer, BUFFER_SIZE);
		line = malloc(sizeof(char) * (size + len + 1));
		if (line)
			line[size + len] = 0;
	}
	if (line)
		ft_memcpy(line + size, buffer, len);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];

	if (fd < 1 || BUFFER_SIZE < 1)
		return (NULL);
	return (create_line(fd, stash, 0));
}
