#include "cub3d_parsing.h"

//return int representing colour usally in agba 4byte int
//flattening a 2d arr into a 1d arr very common memory technique
//basically instead of having 2pts represent you have one 1pt to do it
//in row major order
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