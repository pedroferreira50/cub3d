/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:26:04 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/02 05:18:55 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_line(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**store_cub(const char *filename)
{
	char	**cub_file;
	int		fd;
	int		i;
	char	*line;
	int		count;

	i = 0;
	count = count_line(filename);
	if (count <= 0)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cub_file = malloc(sizeof(char *) * (count + 1));
	if (!cub_file)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		cub_file[i++] = line;
		line = get_next_line(fd);
	}
	cub_file[i] = NULL;
	close(fd);
	return (cub_file);
}
