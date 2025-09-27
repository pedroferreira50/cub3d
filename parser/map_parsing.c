/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:58:52 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/27 18:25:55 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_map_lines(char **cub_file)
{
	int		map_started;
	int		i;
	int		height;

	map_started = 0;
	height = 0;
	i = 0;
	while (cub_file[i])
	{
		if (!map_started && is_map_line(cub_file[i]))
			map_started = 1;
		if (map_started)
		{
			if (!is_map_line(cub_file[i]))
				return (-1);
			height++;
		}
		i++;
	}
	return (height);
}

static t_map	*alloc_map(t_cub_elements *cub3d)
{
	int		height;
	t_map	*map;

	height = count_map_lines(cub3d->cub_file);
	if (height <= 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = malloc(sizeof(char *) * (height + 1));
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	map->map[height] = NULL;
	map->height = height;
	map->width = 0;
	return (map);
}

static bool	copy_map_line(char *line, t_cub_elements *cub3d, int *i)
{
	int	line_len;

	if (!is_map_line(line))
		return (false);
	cub3d->map->map[*i] = ft_strdup(line);
	if (!cub3d->map->map[*i])
		return (false);
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	if (line_len > cub3d->map->width)
		cub3d->map->width = line_len;
	(*i)++;
	return (true);
}

static bool	assign_map_lines(t_cub_elements *cub3d)
{
	int		i;
	int		j;
	bool	map_started;

	map_started = false;
	i = 0;
	j = 0;
	while (cub3d->cub_file[i])
	{
		if (!map_started && is_map_line(cub3d->cub_file[i]))
			map_started = true;
		if (map_started && !copy_map_line(cub3d->cub_file[i], cub3d, &j))
			return (false);
		i++;
	}
	return (true);
}

bool	map_parsing(t_cub_elements *cub3d)
{
	cub3d->map = alloc_map(cub3d);
	if (cub3d->map == NULL)
		return (false);
	if (!assign_map_lines(cub3d))
	{
		free_map(cub3d->map);
		cub3d->map = NULL;
		return (false);
	}
	if (!normalise_map_lines(cub3d->map))
	{
		free_map(cub3d->map);
		cub3d->map = NULL;
		return (false);
	}
	return (true);
}
