/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/26 13:18:49 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
then wallX is computed using the x axis.
Normalize to 0–1 ie get teh fractional part  of the width
then you find that part of the texture
*/

int	get_tex_x(t_ray *ray, t_texture *tex)
{
	int		tex_x;
	double	wall_hit_pos;

	if (ray->vertical_hit)
		wall_hit_pos = ray->hit[Y];
	else
		wall_hit_pos = ray->hit[X];
	wall_hit_pos -= floor(wall_hit_pos / TILE_SIZE) * TILE_SIZE;
	if ((ray->vertical_hit && is_ray_facing(WEST, ray->angle))
		|| (!ray->vertical_hit && is_ray_facing(NORTH, ray->angle)))
		wall_hit_pos = TILE_SIZE - wall_hit_pos;
	tex_x = (int)((wall_hit_pos / TILE_SIZE) * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

t_render_slice	calculate_slice(t_mlx *mlx, t_ray *ray, int col,
		t_cub_elements *elem)
{
	t_render_slice	slice;
	double			corrected_dist;
	double			dist_proj_plane;
	t_texture		*tex;

	corrected_dist = correct_distance(ray, &elem->player);
	dist_proj_plane = ((double)mlx->width / 2.0) / tan(FOV / 2.0);
	slice.line_h = get_line_height(corrected_dist, dist_proj_plane);
	slice.start = (mlx->height / 2) - (slice.line_h / 2);
	if (slice.start < 0)
		slice.start = 0;
	slice.end = slice.start + slice.line_h;
	if (slice.end >= mlx->height)
		slice.end = mlx->height - 1;
	tex = select_texture(elem, ray);
	slice.x = col;
	slice.texx = get_tex_x(ray, tex);
	slice.line_h_d = ((double)TILE_SIZE / corrected_dist) * dist_proj_plane;
	return (slice);
}

static void	draw_wall_texture(t_mlx *mlx, t_texture *tex,
			t_render_slice *slice)
{
	double	step;
	double	tex_y;
	int		y;
	int		tex_y_int;
	int		color;

	step = (double)tex->height / slice->line_h_d;
	tex_y = (slice->start - (mlx->height / 2) + (slice->line_h_d / 2)) * step;
	y = slice->start;
	if (y < 0)
		y = 0;
	if (slice->end > mlx->height)
		slice->end = mlx->height;
	while (y < slice->end)
	{
		tex_y_int = (int)tex_y;
		if (tex_y_int < 0)
			tex_y_int = 0;
		if (tex_y_int >= tex->height)
			tex_y_int = tex->height - 1;
		color = get_tex_pixel(tex, slice->texx, tex_y_int);
		put_pixel(slice->x, y++, color, mlx);
		tex_y += step;
	}
}

void	draw_wall_column(t_mlx *mlx, t_texture *tex, t_render_slice *slice,
		t_cub_elements *elem)
{
	int	y;

	y = slice->start;
	if (y < 0)
		y = 0;
	if (slice->end > mlx->height)
		slice->end = mlx->height;
	fill_ceiling(mlx, elem, slice->x, y);
	draw_wall_texture(mlx, tex, slice);
	fill_floor(mlx, elem, slice->x, slice->end);
}

void	draw_walls(t_mlx *mlx, t_ray *rays, t_cub_elements *elem)
{
	int				x;
	t_ray			*ray;
	t_render_slice	slice;
	t_texture		*tex;

	x = 0;
	while (x < mlx->width)
	{
		ray = &rays[x];
		slice = calculate_slice(mlx, ray, x, elem);
		tex = select_texture(elem, ray);
		draw_wall_column(mlx, tex, &slice, elem);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}
