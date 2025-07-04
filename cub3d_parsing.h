#ifndef CUB3D_PARSING_H
# define CUB3D_PARSING_H

# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdbool.h>

/* typedef struct s_elements {
    bool	no;
    bool	so;
    bool	we;
    bool	ea;
    bool	f;
    bool	c;
}	t_elements; */

typedef struct s_cub_elements
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
}	t_cub_elements;

void	check_arguments(int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);
bool	scan_cub_elements(const char *filename, t_cub_elements *cub3d);

#endif