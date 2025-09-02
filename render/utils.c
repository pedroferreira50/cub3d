/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:23:19 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/11 17:59:34 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// floating pt remainder ie keep between 0 and 2pi for our calcs
// keep remainder of angle / 2pi
float	normalize_angle(float angle)
{
	angle = fmod(angle, TWO_PI);
	if (angle < 0)
		angle += TWO_PI;
	return (angle);
}

// Purpose: Euclidean distance from player to wall hit.
// ie shortest dir distance from pythagorean theorm
float	hit_distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_ray_step	init_ray_step(float x_intercept, float y_intercept, float x_step,
		float y_step)
{
	t_ray_step	step;

	step.next_x = x_intercept;
	step.next_y = y_intercept;
	step.x_step = x_step;
	step.y_step = y_step;
	return (step);
}

float	get_padding(float move)
{
	if (move > 0)
		return (COLLISION_PADDING);
	else
		return (-COLLISION_PADDING);
}

bool	is_wall(t_map *map, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x < 0 || map_y < 0 || map_x >= map->width || map_y >= map->height)
		return (true);
	return (map->map[map_y][map_x] == '1');
}
// printf("is_wall check: x=%.2f, y=%.2f -> map_x=%d, map_y=%d\n", x, y,
//	map_x, map_y);
// printf("Map content at (%d, %d): %c\n", map_y, map_x,
//	map->map[map_y][map_x]);

// void	init_ray_steps(t_ray_step *step, float ray_angle, t_player *player)
// {
// 	// Find ray directions
// 	step->vertical_dir = (cos(ray_angle) > 0) ? EAST : WEST;
// 	step->horizontal_dir = (sin(ray_angle) > 0) ? SOUTH : NORTH;

// 	// VERTICAL STEP SETUP (checking vertical grid lines)
// 	step->x_step = TILE_SIZE;
// 	if (step->vertical_dir == WEST)
// 		step->x_step *= -1;
// 	step->y_step = step->x_step * tan(ray_angle);

// 	step->next_x = floor(player->player_x / TILE_SIZE) * TILE_SIZE;
// 	if (step->vertical_dir == EAST)
// 		step->next_x += TILE_SIZE;
// 	step->next_y = player->player_y + (step->next_x - player->player_x)
//		* tan(ray_angle);

// 	// If ray is facing WEST,
//		adjust starting x slightly back to avoid precision errors
// 	if (step->vertical_dir == WEST)
// 		step->next_x -= 0.0001;
// }
