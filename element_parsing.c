#include "cub3d_parsing.h"

static bool	is_texture_id(char *id)
{
	return (
		ft_strcmp(id, "NO") == 0
		|| ft_strcmp(id, "SO") == 0
		|| ft_strcmp(id, "WE") == 0
		|| ft_strcmp(id, "EA") == 0
	);
}

static bool	check_color_id(char *id, t_cub_elements *cub3d)
{
	if (ft_strcmp(id, "F") == 0 && !cub3d->floor_color_set)
		return (true);
	if (ft_strcmp(id, "C") == 0 && !cub3d->ceiling_color_set)
		return (true);
	return (false);
}

static bool	assign_texture_path(char *id, char *val, t_cub_elements *cub3d)
{
	if (!val || val[0] != '.' || val[1] != '/')
		return (false);
	if (ft_strcmp(id, "NO") == 0 && !cub3d->no_texture)
		cub3d->no_texture = ft_strdup(val);
	else if (ft_strcmp(id, "SO") == 0 && !cub3d->so_texture)
		cub3d->so_texture = ft_strdup(val);
	else if (ft_strcmp(id, "WE") == 0 && !cub3d->we_texture)
		cub3d->we_texture = ft_strdup(val);
	else if (ft_strcmp(id, "EA") == 0 && !cub3d->ea_texture)
		cub3d->ea_texture = ft_strdup(val);
	else
		return (false);
	return (true);
}

static void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static bool	check_element(char *line, t_cub_elements *cub3d)
{
	char	*trimmed;
	char	**sstr;
	char	*id;
	char	*val;
	bool	result;

	trimmed = trim_spaces(line);
	if (ft_strlen(trimmed) == 0)
		return (true);
	sstr = ft_split(trimmed, ' ');
	if (!sstr || !sstr[0])
	{
		if (sstr)
			free_array(sstr);
		return (false);
	}
	id = sstr[0];
	if (sstr[1])
		val = trim_spaces(sstr[1]);
	else
		val = NULL;
	result = false;
	if (val && is_texture_id(id))
		result = assign_texture_path(id, val, cub3d);
	else if (val && check_color_id(id, cub3d))
		result = assign_color(id, val, cub3d);
	free_array(sstr);
	return (result);
}

bool	scan_cub_elements(const char *filename, t_cub_elements *cub3d)
{
	int		fd;
	bool	map_started;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	map_started = false;
	while ((line = get_next_line(fd))) //norm error
	{
		if (!map_started && is_map_line(line))
		{
			if (!cub3d->no_texture || !cub3d->so_texture || !cub3d->we_texture || !cub3d->ea_texture ||
				(!cub3d->floor_color_set || !cub3d->ceiling_color_set))
				return (close_and_free(line, fd, cub3d, false));
			return (close_and_free(line, fd, NULL, true));
		}
		if (!check_element(line, cub3d))
			return (close_and_free(line, fd, cub3d, false));
		free(line);
	}
	return (close_and_free(NULL, fd, cub3d, false));
}
