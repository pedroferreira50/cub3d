#include "cub3d_parsing.h"

static bool	free_array_false(char **array)
{
	int	i;

	if (!array)
		return (false);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (false);
}

static bool	is_valid_rgb_components(char **rgb)
{
	int	i;
	int	val;
	int	j;

	i = 0;
	j = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (!ft_isdigit(rgb[i][j]))
				return (false);
			j++;
		}
		val = ft_atoi(rgb[i]);
		if (val < 0 || val > 255)
			return (false);
		i++;
	}
	return (i == 3);
}

bool	assign_color(char *id, char *val, t_cub_elements *cub3d)
{
	char	**temp;
	int		*target;

	if (!val)
		return (false);
	temp = ft_split(val, ',');
	if (!temp || !is_valid_rgb_components(temp))
		return (free_array_false(temp));
	if (ft_strcmp(id, "F") == 0 && !cub3d->floor_color_set)
		target = cub3d->floor_color;
	else if (ft_strcmp(id, "C") == 0 && !cub3d->ceiling_color_set)
		target = cub3d->ceiling_color;
	else
		return (free_array_false(temp));
	target[0] = ft_atoi(temp[0]);
	target[1] = ft_atoi(temp[1]);
	target[2] = ft_atoi(temp[2]);
	if (target == cub3d->floor_color)
		cub3d->floor_color_set = true;
	else
		cub3d->ceiling_color_set = true;
	free_array_false(temp);
	return (true);
}
