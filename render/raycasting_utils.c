/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:23:33 by gro-donn          #+#    #+#             */
/*   Updated: 2025/07/13 13:23:34 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

// basically each quater circle is pi/2 the one on the right is 0 or 2pi
// defining dir of ray
bool	is_ray_facing(int dir, float angle)
{
	if (dir == NORTH)
		return (angle > PI && angle < TWO_PI);
	if (dir == SOUTH)
		return (!is_ray_facing(NORTH, angle));
	if (dir == WEST)
		return (angle > HALF_PI && angle < 1.5 * PI);
	if (dir == EAST)
		return (!is_ray_facing(WEST, angle));
	return (false);
}
