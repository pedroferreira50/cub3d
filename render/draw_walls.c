
#include "cub3d_parsing.h"

/* Draws vertical wall slices based on distances in `rays[]`
´

*/

void draw_walls(t_cub_elements *app, t_ray *rays)
{
    for (int x = 0; x < app->screen_width; x++)
    {
        t_ray *ray = &rays[x];
        int line_h = (int)(app->screen_height / ray->dist);
        int start = MAX(0, -line_h / 2 + app->screen_height / 2);
        int end = MIN(app->screen_height - 1, line_h / 2 + app->screen_height / 2);

        /* pick texture by ray->wall_content or ray->vertical_hit */
        t_texture *tex = &app->textures[ray->wall_content];
        double wallX = (ray->vertical_hit)
                           ? (app->player.y + ray->dist * ray->dir_y)
                           : (app->player.x + ray->dist * ray->dir_x);
        wallX = wallX - floor(wallX);
        int texX = (int)(wallX * tex->width);
        if (ray->vertical_hit && ray->dir_x > 0)
            texX = tex->width - texX - 1;
        if (!ray->vertical_hit && ray->dir_y < 0)
            texX = tex->width - texX - 1;

        double step = (double)tex->height / line_h;
        double texPos = (start - app->screen_height / 2 + line_h / 2) * step;

        for (int y = start; y < end; y++, texPos += step)
        {
            int texY = (int)texPos & (tex->height - 1);
            int color = get_tex_pixel(tex, texX, texY);
            put_pixel(app->mlx.img_data, x, y, color, &app->mlx);
        }
    }
    mlx_put_image_to_window(app->mlx.mlx_ptr,
                            app->mlx.win_ptr,
                            app->mlx.img_ptr,
                            0, 0);
}
