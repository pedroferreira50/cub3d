#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	char	*path;
	void	*data;
	int		width;
	int		height;
}	t_texture;

typedef struct s_color
{
	int		rgb_color[3];
	bool	color_set;
	int		hex_color;
}	t_color;

typedef struct s_cub_elements
{
	t_texture	*no_text;
	t_texture	*so_text;
	t_texture	*we_text;
	t_texture	*ea_text;
	t_color		*floor_color;
	t_color		*ceiling_color;
	t_map		*map;
}	t_cub_elements;

void	check_arguments(int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);
bool	scan_cub_elements(const char *filename, t_cub_elements *cub3d);
bool	assign_color(char *id, char *val, t_cub_elements *cub3d);
bool	is_map_line(char *line);
bool	close_and_free(char *line, int fd, t_cub_elements *cub3d, bool retu);
void	free_cub_elements(t_cub_elements *cub3d);
char	*trim_spaces(char *str);
bool	map_parsing(const char *filename, t_cub_elements *cub3d);
t_map	*init_map(void);
void	free_map(t_map *map);
void	free_texture(t_texture *texture);

#endif