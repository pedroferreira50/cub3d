/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 02:49:11 by pviegas-          #+#    #+#             */
/*   Updated: 2025/08/28 06:58:14 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	return (read_loop(buffer[fd], line, fd));
}
