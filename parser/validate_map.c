/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:59:25 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/02 05:18:57 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_valid_tile(char c, int flag)
{
	if (flag == 1)
		return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_player(t_cub_elements *cub3d)
{
	int	found;
	int	player_x;
	int	player_y;

	found = 0;
	player_y = 0;
	while (cub3d->map->map[player_y] != NULL)
	{
		player_x = 0;
		while (cub3d->map->map[player_y][player_x] != '\0')
		{
			if (is_valid_tile(cub3d->map->map[player_y][player_x], 1))
			{
				if (found == 0)
				{
					cub3d->map->player_x = player_x;
					cub3d->map->player_y = player_y;
				}
				found++;
			}
			player_x++;
		}
		player_y++;
	}
	return (found);
}

int	flood_fill(char **map_data, int x, int y, int height)
{
	char	c;

	if (y < 0 || y >= height)
		return (0);
	if (x < 0 || x >= (int)strlen(map_data[y]))
		return (0);
	c = map_data[y][x];
	if (c == '1' || c == '*')
		return (1);
	if (!is_valid_tile(c, 0))
		return (0);
	map_data[y][x] = '*';
	return (flood_fill(map_data, x + 1, y, height) && flood_fill(map_data, x
			- 1, y, height) && flood_fill(map_data, x, y + 1, height)
		&& flood_fill(map_data, x, y - 1, height));
}

int	flood_fill_validate(t_map *map)
{
	int		result;
	char	**copy;

	copy = copy_map(map->map, map->height);
	if (!copy)
		return (0);
	result = flood_fill(copy, map->player_x, map->player_y, map->height);
	free_array(copy);
	return (result);
}

bool	validate_map(t_cub_elements *cub3d)
{
	if (find_player(cub3d) != 1)
	{
		printf("Error\nMultiple or no starting positions found.\n");
		return (0);
	}
	if (!flood_fill_validate(cub3d->map))
	{
		printf("Error\nMap is not closed by walls.\n");
		return (0);
	}
	return (1);
}
