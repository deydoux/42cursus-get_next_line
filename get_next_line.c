/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:10 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/22 01:17:32 by deydoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	init_buffer(char **buffer)
{
	size_t	start;
	size_t	len;

	start = 0;
	while (start < BUFFER_SIZE && *buffer[start] != '\n')
		start++;
	while (start + len < BUFFER_SIZE)
	{
		buffer[len] = buffer[start + len];
		len++;
	}
	return (len);
}

static int	find_newline(const char *s)
{
	size_t	len;

	while (len < BUFFER_SIZE && s[len] != '\n')
		len++;
	return (s[len] == '\n');
}

static char	*get_line(char **buffer, size_t size, int init)
{
	size_t	len;
	char	*line;

	if (init)
		len = init_buffer(buffer);
	if (find_newline(*buffer))
	{
		while (buffer[len] != '\n')
			len--;
		line = malloc(sizeof(char) * (size + len + 1));
		line[size + len] = 0;
	}

}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*line;

	if (fd < 1 || BUFFER_SIZE < 1)
		return (NULL);
	return (get_line(&buffer, 0, 1));
}
