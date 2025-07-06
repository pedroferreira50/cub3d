#include "cub3d_parsing.h"

static int	count_map_lines_fd(int fd)
{
	char	*line;
	int		map_started;
	int		height;

	map_started = 0;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started && is_map_line(line))
			map_started = 1;
		if (map_started)
		{
			if (!is_map_line(line))
			{
				free(line);
				return (-1);
			}
			height++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (height);
}

static char	**alloc_map(const char *filename)
{
	int		fd;
	int		height;
	char	**map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	height = count_map_lines_fd(fd);
	close(fd);
	if (height <= 0)
		return (NULL);
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	map[height] = NULL;
	return (map);
}
static bool	copy_map_line(char *line, t_cub_elements *cub3d, int *i)
{
	if (!is_map_line(line))
		return (false);
	cub3d->map[*i] = ft_strdup(line);
	if (!cub3d->map[*i])
		return (false);
	(*i)++;
	return (true);
}

static bool	assign_map_lines(const char *filename, t_cub_elements *cub3d)
{
	int		fd;
	char	*line;
	int		i;
	bool	map_started;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (false);
	i = 0;
	map_started = false;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started && is_map_line(line))
			map_started = true;
		if (map_started && !copy_map_line(line, cub3d, &i))
			return (close_and_free(line, fd, NULL, false));
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (true);
}

bool	map_parsing(const char *filename, t_cub_elements *cub3d)
{
	cub3d->map = alloc_map(filename);
	if (cub3d->map == NULL)
		return (false);
	if (!assign_map_lines(filename, cub3d))
		return (false);
	return (true);
}
