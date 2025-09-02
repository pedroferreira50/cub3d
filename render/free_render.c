/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:45:10 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/26 11:45:11 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// app var means it holds everything i need at run time
// need tp include this !!!!!
// Frees an existing mlx image resource (the one from the previous frame)
// call it before creating a new image, to avoid memory leaks
// It completely destroys the buffer — you cannot draw into it afterwards
void	safe_destroy_image(t_mlx *m, void **img_ptr)
{
	if (m && m->mlx_ptr && img_ptr && *img_ptr)
	{
		mlx_destroy_image(m->mlx_ptr, *img_ptr);
		*img_ptr = NULL;
	}
}

void	clear_image(t_mlx *mlx, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->height)
	{
		x = 0;
		while (x < mlx->width)
		{
			put_pixel(x, y, color, mlx);
			x++;
		}
		y++;
	}
}

void	safe_destroy_window(t_mlx *m)
{
	if (m && m->mlx_ptr && m->win_ptr)
	{
		mlx_destroy_window(m->mlx_ptr, m->win_ptr);
		m->win_ptr = NULL;
	}
}

void	safe_destroy_display_and_free(t_mlx *m)
{
	if (m && m->mlx_ptr)
	{
		mlx_destroy_display(m->mlx_ptr);
		free(m->mlx_ptr);
		m->mlx_ptr = NULL;
	}
}
