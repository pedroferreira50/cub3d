#include "cub3d_parsing.h"

static void	init_struct(t_cub_elements *cub3d)
{
	cub3d->no_texture = NULL;
	cub3d->so_texture = NULL;
	cub3d->we_texture = NULL;
	cub3d->ea_texture = NULL;
	cub3d->floor_color[0] = 0;
	cub3d->floor_color[1] = 0;
	cub3d->floor_color[2] = 0;
	cub3d->ceiling_color[0] = 0;
	cub3d->ceiling_color[1] = 0;
	cub3d->ceiling_color[2] = 0;
	cub3d->map = NULL;
}

int	main(int argc, char **argv)
{
	t_cub_elements	cub3d;

	check_arguments(argc, argv);
	init_struct(&cub3d);
	scan_cub_elements(argv[1], &cub3d);
	
	return (0);
}
