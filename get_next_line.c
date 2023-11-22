/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:10 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/22 15:57:56 by deydoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	init_buffer(char **buffer)
{
	size_t	start;
	size_t	len;

	start = 0;
	len = 0;
	while (start < BUFFER_SIZE && *buffer[start] && *buffer[start] != '\n')
		start++;
	while (start + len < BUFFER_SIZE && *buffer[start + len])
	{
		buffer[len] = buffer[start + len];
		len++;
	}
	return (len);
}

static char	*init_line(size_t size)
{
	char	*line;

	line = malloc(sizeof(char) * (++size + 1));
	line[size--] = 0;
	line[size--] = '\n';
	return (line);
}

static char	*get_line(int fd, char **buffer, size_t size, int init)
{
	size_t	len;
	ssize_t	buffer_len;
	char	*line;

	len = 0;
	if (init)
		buffer_len = init_buffer(buffer);
	else
		buffer_len = read(fd, *buffer, BUFFER_SIZE);
	if (buffer_len < 0)
		return (NULL);
	if (buffer_len < BUFFER_SIZE)
		*buffer[buffer_len] = 0;
	while (len < buffer_len && *buffer[len] && *buffer[len] != '\n')
		len++;
	if (!(buffer_len || init) || !*buffer[len] || *buffer[len] == '\n')
		line = init_line(size + len);
	else
		line = get_line(fd, buffer, size + len, 0);
	if (line)
		while (len-- > 0)
			line[size + len] = buffer[len];
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];

	if (fd < 1 || BUFFER_SIZE < 1)
		return (NULL);
	return (get_line(fd, &buffer, 0, 1));
}
