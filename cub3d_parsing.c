#include "cub3d_parsing.h"

void	free_texture(t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->path)
		free(texture->path);
	if (texture->data)
		free(texture->data);
	free(texture);
}

static t_texture	*init_text_struct(void)
{
	t_texture	*texture;

	texture = malloc(sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->data = NULL;
	texture->height = 0;
	texture->width = 0;
	texture->path = NULL;
	return (texture);
}

static t_color	*init_color_struct(void)
{
	t_color	*color;

	color = malloc(sizeof(t_color));
	if (!color)
		return (NULL);
	color->rgb_color[0] = 0;
	color->rgb_color[1] = 0;
	color->rgb_color[2] = 0;
	color->hex_color = 0;
	color->color_set = false;
	return (color);
}

static bool	init_cub_struct(t_cub_elements *cub3d)
{
	cub3d->no_text = NULL;
	cub3d->so_text = NULL;
	cub3d->we_text = NULL;
	cub3d->ea_text = NULL;
	cub3d->floor_color = NULL;
	cub3d->ceiling_color = NULL;
	cub3d->map = NULL;
	cub3d->no_text = init_text_struct();
	if (!cub3d->no_text)
		return (false);
	cub3d->so_text = init_text_struct();
	if (!cub3d->so_text)
		return (false);
	cub3d->we_text = init_text_struct();
	if (!cub3d->we_text)
		return (false);
	cub3d->ea_text = init_text_struct();
	if (!cub3d->ea_text)
		return (false);
	cub3d->floor_color = init_color_struct();
	if (!cub3d->floor_color)
		return (false);
	cub3d->ceiling_color = init_color_struct();
	if (!cub3d->ceiling_color)
		return (false);
	return (true);
}

static bool	cub3d_parsing(int argc, char **argv, t_cub_elements *cub3d)
{
	check_arguments(argc, argv);
	if (!init_cub_struct(cub3d))
	{
		ft_printf("Error: Failed to initialize cub3d structure\n");
		free_cub_elements(cub3d);
		return (false);
	}
	if (!scan_cub_elements(argv[1], cub3d))
	{
		ft_printf("Error: Failed to parse cub elements\n");
		return (false);
	}
	if (!map_parsing(argv[1], cub3d))
	{
		ft_printf("Error: Failed to parse map\n");
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_cub_elements	cub3d;

	if (!cub3d_parsing(argc, argv, &cub3d))
	{
		ft_printf("Error: Parsing failed\n");
		return (1);
	}
	free_cub_elements(&cub3d);
	return (0);
}
