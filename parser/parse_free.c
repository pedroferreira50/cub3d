/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:25:57 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/02 05:18:51 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	close_and_free(char *line, int fd, t_cub_elements *cub3d, bool retu)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	if (cub3d)
		return (retu);
	return (retu);
}

void	free_cub_elements(t_cub_elements *cub3d, void *mlx_ptr)
{
	if (!cub3d)
		return ;
	if (cub3d->ceiling_color)
		free(cub3d->ceiling_color);
	if (cub3d->floor_color)
		free(cub3d->floor_color);
	if (cub3d->no_text)
		free_texture(cub3d->no_text, mlx_ptr);
	if (cub3d->so_text)
		free_texture(cub3d->so_text, mlx_ptr);
	if (cub3d->we_text)
		free_texture(cub3d->we_text, mlx_ptr);
	if (cub3d->ea_text)
		free_texture(cub3d->ea_text, mlx_ptr);
	if (cub3d->map)
		free_map(cub3d->map);
	if (cub3d->cub_file)
		free_array(cub3d->cub_file);
	cub3d->ceiling_color = NULL;
	cub3d->floor_color = NULL;
	cub3d->no_text = NULL;
	cub3d->so_text = NULL;
	cub3d->we_text = NULL;
	cub3d->ea_text = NULL;
	cub3d->map = NULL;
}

// added this to prevent segfault??cub3d->map = NULL;
void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	free(map);
}
