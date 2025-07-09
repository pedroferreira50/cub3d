#include "cub3d_parsing.h"

bool	is_map_line(char *line)
{
	char	*trimmed;

	trimmed = trim_spaces(line);
	return (trimmed[0] == '1' || trimmed[0] == '0' || trimmed[0] == ' ');
}

bool	close_and_free(char *line, int fd, t_cub_elements *cub3d, bool retu)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	if (cub3d)
		free_cub_elements(cub3d);
	return (retu);
}

void	free_cub_elements(t_cub_elements *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->ceiling_color)
		free(cub3d->ceiling_color);
	if (cub3d->floor_color)
		free(cub3d->floor_color);
	if (cub3d->no_text)
		free_texture(cub3d->no_text);
	if (cub3d->so_text)
		free_texture(cub3d->so_text);
	if (cub3d->we_text)
		free_texture(cub3d->we_text);
	if (cub3d->ea_text)
		free_texture(cub3d->ea_text);
	if (cub3d->map)
		free_map(cub3d->map);
}

char	*trim_spaces(char *str)
{
	int	len;

	while (*str == ' ' || *str == '\t')
		str++;
	len = ft_strlen(str);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'
			|| str[len - 1] == '\n' || str[len - 1] == '\r'))
		str[--len] = '\0';
	return (str);
}
