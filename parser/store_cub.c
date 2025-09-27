/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:26:04 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/27 18:27:27 by pviegas-         ###   ########.fr       */
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

//Map padding
static char	*dup_and_pad_line(const char *src, size_t width)
{
	char	*padded_line;
	size_t	i;

	padded_line = malloc(width + 1);
	if (!padded_line)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n' && i < width)
	{
		padded_line[i] = src[i];
		i++;
	}
	while (i < width)
		padded_line[i++] = ' ';
	padded_line[width] = '\0';
	return (padded_line);
}

bool	normalise_map_lines(t_map *map)
{
	int		y;
	char	*old;
	char	*new;

	y = 0;
	while (y < map->height)
	{
		old = map->map[y];
		new = dup_and_pad_line(old, map->width);
		if (!new)
			return (false);
		free(old);
		map->map[y] = new;
		y++;
	}
	return (true);
}
