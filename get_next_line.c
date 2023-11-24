/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:10 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/24 18:03:22 by deydoux          ###   ########.fr       */
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
		while (stash[start + len] && stash[start + len] != '\n')
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
	if ((size && len < BUFFER_SIZE && !buffer[len]) || buffer[len - 1] == '\n')
	{
		ft_memcpy(stash, buffer, BUFFER_SIZE);
		line = malloc(sizeof(char) * (size + len + 1));
		line[size + len] = 0;
	}
	else
		line = create_line(fd, stash, size + len);
	if (line)
		while (len--)
			line[size + len] = buffer[len];
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];

	if (fd < 1 || BUFFER_SIZE < 1)
		return (NULL);
	return (create_line(fd, stash, 0));
}
