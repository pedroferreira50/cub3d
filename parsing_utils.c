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
	int	i;

	free(cub3d->no_texture);
	free(cub3d->so_texture);
	free(cub3d->we_texture);
	free(cub3d->ea_texture);
	i = 0;
	while (cub3d->map && cub3d->map[i])
		free(cub3d->map[i++]);
	free(cub3d->map);
}

char	*trim_spaces(char *str)
{
	int	len;

	while (*str == ' ')
		str++;
	len = ft_strlen(str);
	while (len > 0 && str[len - 1] == ' ')
		str[--len] = '\0';
	return (str);
}
