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

int	rgb_to_hex(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

bool	assign_color(char *id, char *val, t_cub_elements *cub3d)
{
	char	**temp;
	t_color	*color;
	int		i;

	if (!val)
		return (false);
	temp = ft_split(val, ',');
	if (!temp || !is_valid_rgb_components(temp))
		return (free_array_false(temp));
	if (ft_strcmp(id, "F") == 0 && !cub3d->floor_color->color_set)
		color = cub3d->floor_color;
	else if (ft_strcmp(id, "C") == 0 && !cub3d->ceiling_color->color_set)
		color = cub3d->ceiling_color;
	else
		return (free_array_false(temp));
	i = 0;
	while (i < 3)
	{
		color->rgb_color[i] = ft_atoi(temp[i]);
		i++;
	}
	color->color_set = true;
	color->hex_color = rgb_to_hex(color->rgb_color);
	free_array_false(temp);
	return (true);
}
