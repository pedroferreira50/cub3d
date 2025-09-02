/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:21:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/12 11:34:03 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// basically each quater circle is pi/2 the one on the right is 0 or 2pi
// defining dir of ray
bool	is_ray_facing(int dir, float angle)
{
	bool	result;

	angle = normalize_angle(angle);
	result = false;
	if (dir == NORTH)
		result = (angle > PI && angle < TWO_PI);
	else if (dir == SOUTH)
		result = !is_ray_facing(NORTH, angle);
	else if (dir == WEST)
		result = (angle > HALF_PI && angle < 1.5 * PI);
	else if (dir == EAST)
		result = !is_ray_facing(WEST, angle);
	return (result);
}

void	store_ray_data(t_ray *ray, t_cast *cast, float angle, bool vertical)
{
	ray->angle = angle;
	ray->distance = cast->distance;
	ray->hit[X] = cast->hit[X];
	ray->hit[Y] = cast->hit[Y];
	ray->wall_content = cast->content;
	ray->vertical_hit = vertical;
}
// Pick closer ray
//   if (h.distance < v.distance)
// store_ray_data(&rays[col], &h, angle, /*vertical_hit=*/false);

static void	cast_ray(t_cub_elements *elem, float angle, int col, t_ray *rays)
{
	t_cast	h;
	t_cast	v;
	float	px;
	float	py;

	px = elem->player.player_x;
	py = elem->player.player_y;
	find_horizontal_collision(elem->map, angle, &h, &elem->player);
	find_vertical_collision(elem->map, angle, &v, &elem->player);
	if (!h.hitted)
		h.distance = INFINITY;
	else
		h.distance = hit_distance(px, py, h.hit[X], h.hit[Y]);
	if (!v.hitted)
		v.distance = INFINITY;
	else
		v.distance = hit_distance(px, py, v.hit[X], v.hit[Y]);
	if (h.distance < v.distance)
	{
		store_ray_data(&rays[col], &h, angle, false);
	}
	else
	{
		store_ray_data(&rays[col], &v, angle, true);
	}
}

void	raycasting(t_data *app, t_ray *rays, t_cub_elements *elem)
{
	float	angle;
	int		col;
	float	ray_step;

	ray_step = FOV / (float)app->mlx->width;
	angle = elem->player.angle - HALF_FOV;
	col = 0;
	while (col < app->mlx->width)
	{
		angle = normalize_angle(angle);
		cast_ray(elem, angle, col, rays);
		angle += ray_step;
		col++;
	}
}
/* Cast a ray for each column across the screen
If their FOV is 60 degrees, then:
They can see 30 degrees to the left
And 30 degrees to the right of A
angle = π/2 - π/6 = π/3      // left-most ray
			↑
			|
		/
		/     ← rays go from here ...
		/
		•────────→ π/2 ← straight ahead
		\
		\     ← ... to here
		\
			↓
		π/2 + π/6 = 2π/3        // right-most ray
ach ray_step moves you a tiny bit to the right,
	until you sweep from left to right across the whole FOV.
*/