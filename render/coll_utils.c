/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:23:33 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/12 09:47:55 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	safe_tan(float angle)
{
	float	t;

	t = tan(angle);
	if (fabs(t) < 0.0001f)
	{
		if (t < 0)
			return (0.0001f * -1);
		else
			return (0.0001f * 1);
	}
	return (t);
}

int	get_map_y(t_ray_step *step)
{
	if (step->vertical_dir == NORTH)
		return (((int)(step->next_y) - 1) / TILE_SIZE);
	else
		return ((int)(step->next_y) / TILE_SIZE);
}

t_ray_step	init_horizontal_step(t_player *player, float angle)
{
	float	y_intercept;
	float	x_intercept;
	float	y_step;
	float	x_step;
	float	tan_angle;

	y_intercept = calculate_intercept(angle, player, false);
	tan_angle = safe_tan(angle);
	if (is_ray_facing(SOUTH, angle))
		y_step = TILE_SIZE;
	else
		y_step = -TILE_SIZE;
	x_step = TILE_SIZE / tan_angle;
	if ((x_step > 0 && is_ray_facing(WEST, angle)) || (x_step < 0
			&& is_ray_facing(EAST, angle)))
		x_step = -x_step;
	x_intercept = player->player_x + (y_intercept - player->player_y)
		/ tan_angle;
	return (init_ray_step(x_intercept, y_intercept, x_step, y_step));
}

t_ray_step	init_vertical_step(t_player *player, float angle)
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	float	tan_angle;

	x_intercept = calculate_intercept(angle, player, true);
	tan_angle = safe_tan(angle);
	if (is_ray_facing(EAST, angle))
		x_step = TILE_SIZE;
	else
		x_step = -TILE_SIZE;
	y_step = TILE_SIZE * tan_angle;
	if ((y_step > 0 && is_ray_facing(NORTH, angle)) || (y_step < 0
			&& is_ray_facing(SOUTH, angle)))
		y_step = -y_step;
	y_intercept = player->player_y + (x_intercept - player->player_x)
		* tan_angle;
	return (init_ray_step(x_intercept, y_intercept, x_step, y_step));
}
