/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:10 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/12 09:44:43 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	calculate_intercept(float angle, t_player *player, bool is_vertical)
{
	int	tile_x;
	int	tile_y;

	if (is_vertical)
	{
		tile_x = floor(player->player_x / TILE_SIZE) * TILE_SIZE;
		if (is_ray_facing(EAST, angle))
			return (tile_x + TILE_SIZE);
		else
			return (tile_x - 0.0001f);
	}
	else
	{
		tile_y = floor(player->player_y / TILE_SIZE) * TILE_SIZE;
		if (is_ray_facing(SOUTH, angle))
			return (tile_y + TILE_SIZE);
		else
			return (tile_y - 0.0001f);
	}
}

// Adjust y coordinate for horizontal rays to check correct tile
// based on ray direction
static void	trace_ray(t_map *map, t_ray_step *step, t_cast *h)
{
	int	m_x;
	int	m_y;

	while (1)
	{
		m_x = (int)(step->next_x) / TILE_SIZE;
		m_y = get_map_y(step);
		if (m_x < 0 || m_x >= map->width || m_y < 0 || m_y >= map->height)
		{
			h->hitted = false;
			return ;
		}
		if (map->map[m_y][m_x] == '1')
		{
			h->hit[X] = step->next_x;
			h->hit[Y] = step->next_y;
			h->hitted = true;
			h->content = map->map[m_y][m_x];
			return ;
		}
		step->next_x += step->x_step;
		step->next_y += step->y_step;
	}
}

void	find_horizontal_collision(t_map *map, float angle, t_cast *h,
		t_player *player)
{
	t_ray_step	step;

	step = init_horizontal_step(player, angle);
	if (is_ray_facing(SOUTH, angle))
		step.vertical_dir = SOUTH;
	else
		step.vertical_dir = NORTH;
	trace_ray(map, &step, h);
}

void	find_vertical_collision(t_map *map, float angle, t_cast *v,
		t_player *player)
{
	t_ray_step	step;

	step = init_vertical_step(player, angle);
	if (is_ray_facing(EAST, angle))
		step.vertical_dir = EAST;
	else
		step.vertical_dir = WEST;
	trace_ray(map, &step, v);
}
