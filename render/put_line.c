#include "cub3d_parsing.h"

int get_tex_pixel(t_texture *tex, int x, int y)
{
    int *data = (int *)tex->data;
    return data[y * tex->width + x];
}

void put_pixel(char *img_data, int x, int y, int color, t_mlx *mlx)
{
    int offset = (y * mlx->line_length) + (x * (mlx->bits_per_pixel / 8));
    *(unsigned int *)(img_data + offset) = color;
}