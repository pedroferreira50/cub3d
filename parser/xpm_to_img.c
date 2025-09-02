/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:58:40 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/02 05:19:00 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	load_texture(t_mlx *mlx, t_texture *texture,
		const char *texture_name)
{
	texture->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, texture->path,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		ft_putstr_fd("Error\nFailed to load ", 2);
		ft_putstr_fd((char *)texture_name, 2);
		ft_putstr_fd(" texture: ", 2);
		ft_putstr_fd(texture->path, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	texture->data = mlx_get_data_addr(texture->img_ptr,
			&texture->bits_per_pixel, &texture->line_length, &texture->endian);
	if (!texture->data)
	{
		ft_putstr_fd("Error\nFailed to get data address for ", 2);
		ft_putstr_fd((char *)texture_name, 2);
		ft_putstr_fd(" texture\n", 2);
		return (1);
	}
	return (0);
}

int	xpm_to_img(t_cub_elements *elem, t_mlx *mlx)
{
	if (load_texture(mlx, elem->no_text, "North") != 0)
		return (1);
	if (load_texture(mlx, elem->so_text, "South") != 0)
		return (1);
	if (load_texture(mlx, elem->we_text, "West") != 0)
		return (1);
	if (load_texture(mlx, elem->ea_text, "East") != 0)
		return (1);
	return (0);
}
