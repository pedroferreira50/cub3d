/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:39 by gro-donn          #+#    #+#             */
/*   Updated: 2025/08/26 11:40:02 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_all_safe(t_data *data)
{
	if (!data)
		return ;
	if (data->elem)
	{
		if (data->mlx && data->mlx->mlx_ptr)
			free_cub_elements(data->elem, data->mlx->mlx_ptr);
		else
			free_cub_elements(data->elem, NULL);
		free(data->elem);
		data->elem = NULL;
	}
	if (data->mlx)
	{
		safe_destroy_image(data->mlx, (void **)&data->mlx->img_ptr);
		safe_destroy_window(data->mlx);
		safe_destroy_display_and_free(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
	if (data->rays)
	{
		free(data->rays);
		data->rays = NULL;
	}
	free(data);
}

// Guard: if window/ctx already gone, do nothing
// Destroy previous frame image safely
void	render_frame(t_data *app)
{
	if (!app || app->closing)
		return ;
	if (!app->mlx || !app->mlx->mlx_ptr || !app->mlx->win_ptr)
		return ;
	safe_destroy_image(app->mlx, (void **)&app->mlx->img_ptr);
	app->mlx->img_ptr = mlx_new_image(app->mlx->mlx_ptr, app->mlx->width,
			app->mlx->height);
	if (!app->mlx->img_ptr)
		return ;
	app->mlx->img_data = mlx_get_data_addr(app->mlx->img_ptr,
			&app->mlx->bits_per_pixel, &app->mlx->line_length,
			&app->mlx->endian);
	clear_image(app->mlx, 0x000000);
	if (!app->rays || app->rays_w != app->mlx->width)
	{
		free(app->rays);
		app->rays = malloc(sizeof(t_ray) * app->mlx->width);
		app->rays_w = app->mlx->width;
	}
	if (!app->rays)
		return ;
	raycasting(app, app->rays, app->elem);
	draw_walls(app->mlx, app->rays, app->elem);
}

// 'w' eycode == 119)
// printf("Key pressed: %d\n", keycode);
int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == 119)
		data->keys.w = 1;
	else if (keycode == 115)
		data->keys.s = 1;
	else if (keycode == 97)
		data->keys.a = 1;
	else if (keycode == 100)
		data->keys.d = 1;
	else if (keycode == 65361)
		data->keys.left = 1;
	else if (keycode == 65363)
		data->keys.right = 1;
	else if (keycode == 65307)
		handle_close(data);
	return (0);
}

int	handle_keyrelease(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	else if (keycode == KEY_S)
		data->keys.s = 0;
	else if (keycode == KEY_A)
		data->keys.a = 0;
	else if (keycode == KEY_D)
		data->keys.d = 0;
	else if (keycode == KEY_LEFT)
		data->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}
