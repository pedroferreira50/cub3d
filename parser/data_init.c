/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:22:24 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/02 05:26:09 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	init_mlx(t_mlx *mlx)
{
	mlx->width = WIDTH;
	mlx->height = HEIGHT;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
	{
		ft_putstr_fd("Error\nFailed to initialize mlx\n", 2);
		return (EXIT_FAILURE);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "Map Display");
	if (mlx->win_ptr == NULL)
	{
		ft_putstr_fd("Error\nFailed to create a new window\n", 2);
		return (EXIT_FAILURE);
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->width, mlx->height);
	if (!mlx->img_ptr)
	{
		ft_putstr_fd("Error\nFailed to create image buffer\n", 2);
		return (EXIT_FAILURE);
	}
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel,
			&mlx->line_length, &mlx->endian);
	return (EXIT_SUCCESS);
}

static int	map_text_init(t_data *data)
{
	if (!data->elem->map)
	{
		ft_putstr_fd("Error\nMap not initialized\n", 2);
		return (1);
	}
	if (xpm_to_img(data->elem, data->mlx) != 0)
	{
		ft_putstr_fd("Error\nTexture loading failed\n", 2);
		return (1);
	}
	return (0);
}

int	data_init(int argc, char **argv, t_data *data)
{
	data->elem = malloc(sizeof(t_cub_elements));
	if (!data->elem)
		return (1);
	data->mlx = malloc(sizeof(t_mlx));
	if (!data->mlx)
		return (1);
	data->mlx->mlx_ptr = NULL;
	data->mlx->win_ptr = NULL;
	if (!cub3d_parsing(argc, argv, data->elem))
	{
		return (1);
	}
	if (init_mlx(data->mlx) != 0)
	{
		ft_putstr_fd("Error\nMLX initialization failed\n", 2);
		return (1);
	}
	if (map_text_init(data) != 0)
	{
		return (1);
	}
	return (0);
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	return (map);
}
