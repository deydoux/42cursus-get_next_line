/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deydoux <deydoux@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:03:40 by deydoux           #+#    #+#             */
/*   Updated: 2023/11/30 16:00:56 by deydoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/select.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_SETSIZE
#  define FD_SETSIZE 1024
# endif

char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_bzero(void *s, size_t n);

#endif
