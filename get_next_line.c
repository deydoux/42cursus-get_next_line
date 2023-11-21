/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:02:10 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/21 17:39:55 by deydoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_start(char *buffer)
{
	size_t	buffer_len;
	char	*start;

	while (buffer[buffer_len] && buffer[buffer_len] != '\n')
		buffer++;
	return (start);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*start;
	char		*line;
	size_t		line_len;

	if (fd < 1 || BUFFER_SIZE < 1)
		return (NULL);
	start = get_start(buffer);
	line_len = 0;
	return (line);
}
