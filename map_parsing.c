#include "cub3d_parsing.h"

// move to a init structs file
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

// move to utils or a free file
void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	free(map);
}

static int	count_map_lines(int fd)
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

static t_map	*alloc_map(const char *filename)
{
	int		fd;
	int		height;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	height = count_map_lines(fd);
	close(fd);
	if (height <= 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->map = malloc(sizeof(char *) * (height + 1));
	if (!map->map)
	{
		free(map);
		return (NULL);
	}
	map->map[height] = NULL;
	map->height = height;
	map->width = 0;
	return (map);
}

static bool	copy_map_line(char *line, t_cub_elements *cub3d, int *i)
{
	int	line_len;

	if (!is_map_line(line))
		return (false);
	cub3d->map->map[*i] = ft_strdup(line);
	if (!cub3d->map->map[*i])
		return (false);
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	if (line_len > cub3d->map->width)
		cub3d->map->width = line_len;
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
	{
		free_cub_elements(cub3d);
		return (false);
	}
	if (!assign_map_lines(filename, cub3d))
	{
		free_map(cub3d->map);
		cub3d->map = NULL;
		free_cub_elements(cub3d);
		return (false);
	}
	//validate_map(cub3d->map); // work in progress map validation
	return (true);
}
