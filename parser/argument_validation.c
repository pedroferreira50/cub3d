/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas- <pviegas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:26:04 by pviegas-          #+#    #+#             */
/*   Updated: 2025/09/27 18:26:51 by pviegas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static int	is_cub_file(const char *filename)
{
	int	len;
	int	fd;

	len = ft_strlen(filename);
	if (len > 4 && ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		ft_putstr_fd("Error\nFile must have a .cub extension.\n", 2);
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nThe file does not exist\n", 2);
		return (1);
	}
	close(fd);
	return (0);
}

void	free_at_args(t_data *data)
{
	if (data->elem)
		free(data->elem);
	if (data->mlx)
		free(data->mlx);
	if (data->rays)
		free(data->rays);
	if (data)
		free(data);
}

void	check_arguments(int argc, char **argv, t_data *data)
{
	if (argc < 2)
	{
		ft_putstr_fd("Error\nNo file provided. - ./program <map.cub>\n", 2);
		free_at_args(data);
		exit(1);
	}
	else if (argc > 2)
	{
		ft_putstr_fd("Error\nToo many arguments. - ./program <map.cub>\n", 2);
		free_at_args(data);
		exit(1);
	}
	else if (is_cub_file(argv[1]))
	{
		free_at_args(data);
		exit(1);
	}
}
