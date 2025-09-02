/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:48:22 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/26 11:48:23 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	correct_distance(t_ray *ray, t_player *player)
{
	double	corrected;

	corrected = ray->distance * cos(ray->angle - player->angle);
	if (corrected <= 0.00001)
		corrected = 0.00001;
	return (corrected);
}

int	get_line_height(double corrected_dist, double dist_proj_plane)
{
	double	raw_line_h;
	int		draw_line_h;

	raw_line_h = ((double)TILE_SIZE / corrected_dist) * dist_proj_plane;
	draw_line_h = (int)raw_line_h;
	if (draw_line_h < 1)
		draw_line_h = 1;
	return (draw_line_h);
}
