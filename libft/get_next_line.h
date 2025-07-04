/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:49:25 by pviegas-          #+#    #+#             */
/*   Updated: 2024/11/14 03:39:11 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "libft.h"

int			newline_checker(char **line, char *buffer);
int			ft_strlen2(char const *str1);
char		*get_next_line(int fd);
char		*ft_strjoin(char const *str1, char const *str2);
char		*buffer_full_clear(int fd, char **buffer, char *line);
char		*read_loop(char	*buffer, char *line, int fd);
void		buffer_shift_left(char *buffer);

#endif
