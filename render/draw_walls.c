/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:22:05 by gro-donn          #+#    #+#             */
/*   Updated: 2025/07/13 21:34:01 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parsing.h"

/* Draws vertical wall slices based on distances in `rays[]`
*/

t_texture *select_texture(t_cub_elements *app, t_ray *ray)
{
    if (ray->vertical_hit)
    {
        if (ray->wall_content == 'E') return &app->ea_texture;
        else                          return &app->we_texture;
    }
    else
    {
        if (ray->wall_content == 'N') return &app->no_texture;
        else                          return &app->so_texture;
    }
}

int get_tex_x(t_ray *ray, t_texture *tex, t_player *p)
{
    double wallX;

    if (ray->vertical_hit)
        wallX = p->y + ray->dist * sin(ray->angle);
    else
        wallX = p->x + ray->dist * cos(ray->angle);

    wallX -= floor(wallX);
    int texX = (int)(wallX * tex->width);

    if ((ray->vertical_hit && ray->angle < M_PI) ||
        (!ray->vertical_hit && ray->angle > M_PI_2 && ray->angle < 3 * M_PI_2))
        texX = tex->width - texX - 1;

    return texX;
}

void draw_wall_column(t_mlx *mlx, t_texture *tex, t_render_slice *slice)
{
    double step = (double)tex->height / slice->line_h;
    double texPos = (slice->start - mlx->height / 2 + slice->line_h / 2) * step;

    int y = slice->start;
    while (y < slice->end)
    {
        int texY = (int)texPos % tex->height;
        texPos += step;

        int color = get_tex_pixel(tex, slice->texX, texY);
        put_pixel(mlx->img_data, slice->x, y, color, mlx);
        y++;
    }
}



void draw_walls(t_cub_elements *app, t_ray *rays)
{
    int x = 0;
    while (x < app->mlx.width)
    {
        t_ray *ray = &rays[x];
        int line_h = app->mlx.height / ray->dist;
        int start = -line_h / 2 + app->mlx.height / 2;
        int end = line_h / 2 + app->mlx.height / 2;

        if (start < 0)
            start = 0;
        if (end >= app->mlx.height)
            end = app->mlx.height - 1;

        t_texture *tex = select_texture(app, ray);
        int texX = get_tex_x(ray, tex, &app->player);

        t_render_slice slice;
        slice.x = x;
        slice.texX = texX;
        slice.start = start;
        slice.end = end;
        slice.line_h = line_h;

       //  int ceiling_hex = rgb_to_hex(app->ceiling);
        fill_column(&app->mlx, x, 0, start, app->ceiling);

        // 🎨 Draw wall
        draw_wall_column(&app->mlx, tex, &slice);

        // 🎨 Fill floor
       // int floor_hex = rgb_to_hex(app->floor);
        fill_column(&app->mlx, x, end, app->mlx.height, app->floor);

        x++;

        draw_wall_column(&app->mlx, tex, &slice);
      

        x++;
    }
    mlx_put_image_to_window(app->mlx.mlx_ptr, app->mlx.win_ptr, app->mlx.img_ptr, 0, 0);
}
