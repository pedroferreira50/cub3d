/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:21:56 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/12 09:18:33 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// return int representing colour
// top check prevents reading outside texture arr
// convert bits to bytes by /8 32-bit → 4 bytes per pixel (RGBA
// Calculating the memory address of the pixel
// 3bits 24 bits per pixel ( rbg no alpha channel).
int	get_tex_pixel(t_texture *tex, int x, int y)
{
	int				bpp;
	unsigned char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	bpp = tex->bits_per_pixel / 8;
	pixel = (unsigned char *)tex->data + y * tex->line_length + x * bpp;
	if (bpp == 4)
		return (*(unsigned int *)pixel);
	if (bpp == 3)
		return (pixel[0] | (pixel[1] << 8) | (pixel[2] << 16));
	return (0);
}

void	fill_ceiling(t_mlx *mlx, t_cub_elements *elem, int x, int start)
{
	int	y;

	y = 0;
	while (y < start)
	{
		put_pixel(x, y, elem->ceiling_color->hex_color, mlx);
		y++;
	}
}

void	fill_floor(t_mlx *mlx, t_cub_elements *elem, int x, int start)
{
	int	y;

	y = start;
	while (y < mlx->height)
	{
		put_pixel(x, y, elem->floor_color->hex_color, mlx);
		y++;
	}
}

void	put_pixel(int x, int y, int color, t_mlx *mlx)
{
	int	offset;

	if (x < 0 || y < 0 || x >= mlx->width || y >= mlx->height)
		return ;
	offset = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
	if (offset < 0 || offset >= mlx->height * mlx->line_length)
		return ;
	*(unsigned int *)(mlx->img_data + offset) = color;
}

t_texture	*select_texture(t_cub_elements *app, t_ray *ray)
{
	if (ray->vertical_hit)
	{
		if (is_ray_facing(EAST, ray->angle))
			return (app->ea_text);
		else
			return (app->we_text);
	}
	else
	{
		if (is_ray_facing(NORTH, ray->angle))
			return (app->no_text);
		else
			return (app->so_text);
	}
}
