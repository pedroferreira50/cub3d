/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:16:59 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/27 17:40:03 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// had to update this to avoid double free 
//was causing segfault just put the ptr to null
// Corrected: Destroy texture->img_ptr, not just texture->data
void	free_texture(t_texture *texture, void *mlx_ptr)
{
	if (!texture)
		return ;
	if (mlx_ptr && texture->img_ptr)
	{
		mlx_destroy_image(mlx_ptr, texture->img_ptr);
		texture->img_ptr = NULL;
	}
	if (texture->path)
	{
		free(texture->path);
		texture->path = NULL;
	}
	free(texture);
}

static t_texture	*init_text_struct(void)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->data = NULL;
	texture->height = 0;
	texture->width = 0;
	texture->path = NULL;
	texture->bits_per_pixel = 0;
	texture->line_length = 0;
	texture->endian = 0;
	texture->img_ptr = NULL;
	return (texture);
}
// ADDED THIS: texture->bits_per_pixel = 0;
// ADD THIS: texture->line_length = 0;
// <-- ADD THIS: texture->endian = 0;

static t_color	*init_color_struct(void)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->rgb_color[0] = 0;
	color->rgb_color[1] = 0;
	color->rgb_color[2] = 0;
	color->hex_color = 0;
	color->color_set = false;
	return (color);
}

static bool	init_cub_struct(t_cub_elements *cub3d)
{
	cub3d->no_text = NULL;
	cub3d->so_text = NULL;
	cub3d->we_text = NULL;
	cub3d->ea_text = NULL;
	cub3d->floor_color = NULL;
	cub3d->ceiling_color = NULL;
	cub3d->map = NULL;
	cub3d->cub_file = NULL;
	cub3d->no_text = init_text_struct();
	cub3d->so_text = init_text_struct();
	cub3d->we_text = init_text_struct();
	cub3d->ea_text = init_text_struct();
	cub3d->floor_color = init_color_struct();
	cub3d->ceiling_color = init_color_struct();
	if (!cub3d->no_text || !cub3d->so_text || !cub3d->we_text || !cub3d->ea_text
		|| !cub3d->floor_color || !cub3d->ceiling_color)
		return (false);
	return (true);
}

bool	cub3d_parsing(int argc, char **argv, t_data *data)
{
	check_arguments(argc, argv, data);
	if (!init_cub_struct(data->elem))
	{
		ft_putstr_fd("Error\nFailed to initialize cub3d structure\n", 2);
		return (false);
	}
	if (!scan_cub_elements(argv[1], data->elem, data->elem->ceiling_color,
			data->elem->floor_color))
	{
		ft_putstr_fd("Error\nFailed to parse cub elements\n", 2);
		return (false);
	}
	if (!map_parsing(data->elem))
	{
		ft_putstr_fd("Error\nFailed to parse map\n", 2);
		return (false);
	}
	if (!validate_map(data->elem))
	{
		ft_putstr_fd("Error\nFailed to parse map\n", 2);
		return (false);
	}
	return (true);
}
